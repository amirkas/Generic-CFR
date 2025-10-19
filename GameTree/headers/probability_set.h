//
// Created by Amir on 10/18/25.
//

#ifndef GENERICCFRLIB_PROBABILITY_SET_H
#define GENERICCFRLIB_PROBABILITY_SET_H

#endif //GENERICCFRLIB_PROBABILITY_SET_H

#include<vector>


template<typename float_type> class ProbabilitySet {

    uint8_t num_children = 0;
    std::vector<float_type> probabilities;

public:

    ProbabilitySet() = default;
    explicit ProbabilitySet(uint8_t num_children) {this->num_children = num_children;}

    float_type GetProbability(int index);

    uint8_t RandomChildIndex();

};
