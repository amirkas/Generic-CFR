//
// Created by Amir on 10/18/25.
//
#pragma once

#include <infoset.h>

template <typename float_type>
InfoSet<float_type>::InfoSet(uint8_t num_actions) {
    this->num_actions = num_actions;;
    this->Reset();
}

template <typename float_type>
void InfoSet<float_type>::Reset() {
    auto uniform_probability = static_cast<float_type>(1 / num_actions);
    auto zero = static_cast<float_type>(0);
    this->curr_strategy.insert(this->curr_strategy.begin(), num_actions, uniform_probability);
    this->cum_strategy.insert(this->curr_strategy.begin(), num_actions, zero);
    this->cum_regret.insert(this->curr_strategy.begin(), num_actions, zero);
}

template<typename float_type>
uint8_t InfoSet<float_type>::NumActions() {
    return static_cast<uint8_t>(3 * sizeof(float_type) * this->num_actions);
}

template<typename float_type>
float_type InfoSet<float_type>::GetCurrentStrategy(int index) {
    return this->curr_strategy.at(index);
}

template<typename float_type>
float_type InfoSet<float_type>::GetCumulativeStrategy(int index) {
    return this->cum_strategy.at(index);
}

template<typename float_type>
float_type InfoSet<float_type>::GetCumulativeRegret(int index) {
    return this->cum_regret.at(index);
}

template<typename float_type>
void InfoSet<float_type>::SetCurrentStrategy(int index, float_type prob) {
    this->curr_strategy[index] = prob;
}

template<typename float_type>
void InfoSet<float_type>::SetCumulativeStrategy(int index, float_type prob) {
    this->cum_strategy[index] = prob;
}

template<typename float_type>
void InfoSet<float_type>::SetCumulativeRegret(int index, float_type regret) {
    this->cum_regret[index] = regret;
}

template<typename float_type>
void InfoSet<float_type>::AddToCumulativeStrategy(int index, float_type prob) {
    this->cum_strategy[index] += prob;
}

template<typename float_type>
void InfoSet<float_type>::AddToCumulativeRegret(int index, float_type regret) {
    this->cum_regret[index] += regret;
}
