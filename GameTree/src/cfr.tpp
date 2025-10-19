//
// Created by Amir on 10/18/25.
//
#pragma once

#include <cfr.h>
#include <node.h>
#include <iostream>
#include <ostream>

/** CFR Helper Function Forward Declarations **/

template <typename float_type>
float_type WalkTree(
    std::shared_ptr<Node<float_type>> node, int player_id,
    std::vector<float_type> &player_reach_probs, bool with_sampling);

template<typename float_type>
float_type WalkTreePlayerNode(std::shared_ptr<PlayerNode<float_type>> node, int player_id,
    std::vector<float_type> &player_reach_probs, bool with_sampling);

template<typename float_type>
float_type WalkTreeChanceNode(std::shared_ptr<ChanceNode<float_type>> node, int player_id,
    std::vector<float_type> &player_reach_probs, bool with_sampling);

template<typename float_type>
float_type WalkTreeTerminalNode(std::shared_ptr<TerminalNode<float_type>> node);

template<typename float_type>
void RegretMatching(std::shared_ptr<InfoSet<float_type>> info_set);

/** CFR Helper Function Definitions **/

template<typename float_type>
float_type WalkTreePlayerNode(std::shared_ptr<PlayerNode<float_type>> node, int player_id,
    std::vector<float_type> &player_reach_probs, const bool with_sampling) {

    float val = 0;
    const uint8_t num_children = node->NumChildren();
    std::vector<std::shared_ptr<Node<float_type>>> children = node->Children();
    std::vector<float> child_utilities(num_children, 0);
    std::shared_ptr<InfoSet<float_type>> info_set = node->InfoSet();

    for (uint8_t action_index = 0; action_index < num_children; action_index++) {
        std::shared_ptr<Node<float_type>> child = children[action_index];
        float_type current_strat_prob = info_set->GetCurrentStrategy(action_index);

        // Store the original player reach probability before modifying it
        float_type original_reach_prob = player_reach_probs[player_id];

        // Modify the player reach probability using the current strategy
        player_reach_probs[player_id] *= current_strat_prob;

        float_type child_utility = WalkTree<float_type>(child, player_id, player_reach_probs, with_sampling);

        // Restore the original player reach probability before modifying it again for the next action
        player_reach_probs[player_id] = original_reach_prob;

        child_utilities.at(action_index) = child_utility;
        val += current_strat_prob * child_utility;
    }
    if (node->PlayerID() == player_id) {
        float_type player_reach_prob = player_reach_probs[player_id];
        float_type not_player_reach_prob = 1 - player_reach_prob;
        for (uint8_t action_index = 0; action_index < num_children; action_index++) {
            info_set->AddToCumulativeRegret(not_player_reach_prob * (child_utilities.at(action_index) - val), action_index);
            info_set->AddToCumulativeStrategy(player_reach_prob * info_set->GetCurrentStrategy(action_index), action_index);
        }
        RegretMatching<float_type>(info_set);
    }
    return val;
}

template<typename float_type>
float_type WalkTreeChanceNode(std::shared_ptr<ChanceNode<float_type>> node, int player_id,
    std::vector<float_type> &player_reach_probs, bool with_sampling) {

    if (with_sampling) {
        uint8_t child_index = node->GetRandomChildIndex();
        float_type child_probability = node->GetChildProbability(child_index);
        std::shared_ptr<Node<float_type>> child = node->GetChild(child_index);
        return WalkTree(child, player_id, player_reach_probs, with_sampling);
    }

    const uint8_t num_children = node->GetNumChildren();
    float_type average_utility = 0;
    for (uint8_t child_index = 0; child_index < num_children; child_index++) {
        std::shared_ptr<Node<float_type>> child = node->GetChild(child_index);
        std::shared_ptr<Node<float_type>> child_probability = node->GetChild(child_index);
        average_utility += child_probability * WalkTree<float_type>(child, player_id, player_reach_probs, with_sampling);
    }
    return average_utility;
}

template<typename float_type>
float_type WalkTreeTerminalNode(std::shared_ptr<TerminalNode<float_type>> node) {
    return node->GetUtility();
}

template<typename float_type>
void RegretMatching(std::shared_ptr<InfoSet<float_type>> info_set) {
    float_type regret_sum = 0;
    for (uint8_t i_action = 0; i_action < info_set->NumActions(); i_action++)
    {
        float_type action_regret = info_set->GetCumulativeRegret(i_action);
        if (action_regret > 0)
        {
            info_set->SetCurrentStrategy(action_regret, i_action);
            regret_sum += action_regret;
        }
        else
        {
            info_set->SetCurrentStrategy(0.0, i_action);
        }
    }
    const float_type uniform_prob = 1.0 / static_cast<float_type>(info_set->NumActions());
    for (int i_action = 0; i_action < info_set->NumActions(); i_action++)
    {
        if (regret_sum > 0)
        {
            float_type curr_strat = info_set->GetCurrentStrategy(i_action);
            info_set->SetCurrentStrategy(curr_strat / regret_sum, i_action);
        }
        else
        {
            info_set->SetCurrentStrategy(uniform_prob, i_action);
        }
    }
}

template <typename float_type>
float_type WalkTree(
    std::shared_ptr<Node<float_type>> node, int player_id,
    std::vector<float_type> &player_reach_probs, bool with_sampling) {

    auto player_node = dynamic_cast<std::shared_ptr<PlayerNode<float_type>>>(node);
    if (player_node) {
        return WalkTreePlayerNode<float_type>(player_node, player_id, player_reach_probs, with_sampling);
    }

    auto chance_node = dynamic_cast<std::shared_ptr<ChanceNode<float_type>>>(node);
    if (chance_node) {
        return WalkTreeChanceNode<float_type>(chance_node, player_id, player_reach_probs, with_sampling);
    }

    auto terminal_node = dynamic_cast<std::shared_ptr<TerminalNode<float_type>>>(node);
    if (terminal_node) {
        return WalkTreeTerminalNode<float_type>(terminal_node);
    }

    return 0;
}

template <typename float_type>
void ExploreTreeForReset(std::shared_ptr<Node<float_type>> node) {

    auto player_node = dynamic_cast<std::shared_ptr<PlayerNode<float_type>>>(node);
    if (player_node) {
        player_node->InfoSet()->Reset();
        for (std::shared_ptr<Node<float_type>> child : node->GetChildren()) {
            ExploreTreeForReset(child);
        }
    }
    auto chance_node = dynamic_cast<std::shared_ptr<ChanceNode<float_type>>>(node);
    if (chance_node) {
        for (std::shared_ptr<Node<float_type>> child : node->GetChildren()) {
            ExploreTreeForReset(child);
        }
    }
}


template <typename float_type>
void CFR<float_type>::ResetTree() {
    ExploreTreeForReset(this->root_node);
}

template <typename float_type>
void CFR<float_type>::RunCFR(long long iterations, bool chance_sampling) {

    std::vector<float_type> player_reach_probs;
    std::vector<float_type> player_expected_values;
    player_reach_probs.insert(player_reach_probs.begin(), this->num_players, static_cast<float_type>(1.0));
    player_expected_values.insert(player_reach_probs.begin(), this->num_players, static_cast<float_type>(0.0));

    for (long long i = 0; i < iterations; i++) {
        for (int player_id = 0; player_id < this->num_players; player_id++) {
            float_type player_ev = WalkTree(this->root_node, player_id, player_reach_probs, chance_sampling);
            player_expected_values.at(player_id) = player_ev;
        }
    }
    std::cout << "Player Expected Values: " << std::endl;
    for (int player_id = 0; player_id < this->num_players; player_id++) {
        float_type player_ev = player_expected_values.at(player_id);
        std::cout << "Player " << player_id << ": " << player_ev << std::endl;
    }
}

