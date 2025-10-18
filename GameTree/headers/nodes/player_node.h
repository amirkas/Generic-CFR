//
// Created by Amir on 10/18/25.
//

#ifndef GENERICCFRLIB_PLAYER_NODE_H
#define GENERICCFRLIB_PLAYER_NODE_H

#endif //GENERICCFRLIB_PLAYER_NODE_H

#include <node.h>

template<typename float_type>
class PlayerNode : public NonTerminalNode<float_type> {

    uint8_t player_id = 0;
    std::shared_ptr<InfoSet<float_type>> info_set = nullptr;

public:

    PlayerNode() = default;

    uint8_t NumChildren() override;

    uint8_t PlayerID() const {return this->player_id;}
    std::shared_ptr<InfoSet<float_type>> InfoSet() {return this->info_set;}

};