//
// Created by Amir on 10/18/25.
//

#ifndef GENERICCFRLIB_TERMINAL_NODE_H
#define GENERICCFRLIB_TERMINAL_NODE_H

#endif //GENERICCFRLIB_TERMINAL_NODE_H

#include <node.h>

template<typename float_type>
class TerminalNode : public Node<float_type> {

    float_type utility;

public:

    TerminalNode() = default;
    explicit TerminalNode(float_type utility) {this->utility = utility;}

    float_type GetUtility() {return this->utility;}

};