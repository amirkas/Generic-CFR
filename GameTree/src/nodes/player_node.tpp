//
// Created by Amir on 10/18/25.
//
#pragma once

#include <node.h>
#include <player_node.h>
#include <infoset.h>

template <typename float_type>
uint8_t PlayerNode<float_type>::NumChildren() {
    return this->info_set->NumChildren();
}

