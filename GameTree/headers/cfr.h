//
// Created by Amir on 10/18/25.
//

#ifndef GENERICCFRLIB_CFR_H
#define GENERICCFRLIB_CFR_H

#endif //GENERICCFRLIB_CFR_H

#include <node.h>
#include <player_node.h>
#include <chance_node.h>
#include <terminal_node.h>
#include <infoset.h>


template<typename float_type>
class CFR {

    static_assert(std::is_base_of_v<float, float_type>, "float_type must be a float");

    std::shared_ptr<Node>  root_node;
    int num_players = 0;
    long long _tree_size = 0;

public:

    void ResetTree();

    void RunCFR(long long iterations, bool chance_sampling);

    void RunCFR(float accuracy, bool chance_sampling);

};
