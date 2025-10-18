//
// Created by Amir on 10/18/25.
//

#ifndef GENERICCFRLIB_CHANCE_NODE_H
#define GENERICCFRLIB_CHANCE_NODE_H

#endif //GENERICCFRLIB_CHANCE_NODE_H

#include <node.h>

template<typename float_type>
class ChanceNode : public NonTerminalNode<float_type> {

    std::shared_ptr<ProbabilitySet<float_type>> probabilities = nullptr;

public:

    ChanceNode() = default;

    uint8_t NumChildren() override;

    std::shared_ptr<ProbabilitySet<float_type>> Probabilities() {return this->probabilities;}

    std::shared_ptr<ProbabilitySet<float_type>> GetProbability(int index) {return this->probabilities;}

    uint8_t GetRandomChildIndex();

};