//
//  node.cpp
//  
//
//  Created by Amir on 10/10/25.
//

#include <stdio.h>
#include <string>
#include <memory>
#include <utility>
#include <vector>

#include <node.h>

template<typename float_type>
std::shared_ptr<Node<float_type>> cast_to_derived_node(std::shared_ptr<Node<float_type>> node) {

    auto player = dynamic_cast<std::shared_ptr<PlayerNode<float_type>>>(node);
    if (player) {
        return player;
    }

    auto chance = dynamic_cast<std::shared_ptr<ChanceNode<float_type>>>(node);
    if (chance) {
        return chance;
    }

    auto terminal = dynamic_cast<std::shared_ptr<TerminalNode<float_type>>>(node);
    if (terminal) {
        return terminal;
    }
    return nullptr;
}



/// @brief Constructor for Node
template <typename float_type>
Node<float_type>::Node() {
    next_node = nullptr;
}

/// @brief Constructor for Node
/// @param next_node_address Address of the next node in the Node Linked List
template <typename float_type>
Node<float_type>::Node(std::shared_ptr<Node> next_node_address) {
    next_node = std::move(next_node_address);
}

/// @brief Constructor for Non Terminal Node (Player Node or Chance Nodes)
template <typename float_type>
NonTerminalNode<float_type>::NonTerminalNode() {
    this->first_child = nullptr;
    this->num_children = 0;
}

/// @brief Constructor for Non Terminal Node (Player Node or Chance Nodes)
/// @param first_child_p Address of the head of the Linked List containing all child nodes
template <typename float_type>
NonTerminalNode<float_type>::NonTerminalNode(std::shared_ptr<Node<float_type>> first_child_p) {
    first_child = std::move(first_child_p);
    num_children = static_cast<uint8_t>(this->Children().size());
}

/// @brief Gets a vector of Node addresses for all children of the current node
/// @return Node address vector
template <typename float_type>
std::vector<std::shared_ptr<Node<float_type>>> NonTerminalNode<float_type>::Children() const {

    std::vector<std::shared_ptr<Node<float_type>>> children;
    std::shared_ptr<Node<float_type>> tmp = this->first_child;

    while (tmp != nullptr) {
        children.push_back(tmp);
        tmp = tmp->next_node;
    }
    return children;
}

template<typename float_type>
std::shared_ptr<Node<float_type>> NonTerminalNode<float_type>::GetChild(const uint8_t index) {

    uint8_t i = 0;
    std::shared_ptr<Node<float_type>> curr = this->first_child;
    while (curr != nullptr) {
        if (i == index) {
            return curr;
        }
        curr = curr->next_node;
        i++;
    }
    return nullptr;
}


