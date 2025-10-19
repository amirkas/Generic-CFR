//
// Created by Amir on 10/18/25.
//

#include <random>

#include <probability_set.h>

template <typename float_type>
float_type ProbabilitySet<float_type>::GetProbability(int index) {
    return this->probabilities[index];
}

template <typename float_type>
uint8_t ProbabilitySet<float_type>::RandomChildIndex() {

    std::random_device rd;
    std::mt19937 gen(rd());

    std::discrete_distribution<std::size_t> distribution(this->probabilities.begin(), this->probabilities.end());
    return static_cast<uint8_t>(distribution(gen));
}
