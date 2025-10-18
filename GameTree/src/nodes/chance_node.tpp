//
// Created by Amir on 10/18/25.
//

#include <node.h>
#include <chance_node.h>
#include <probability_set.h>

template<typename float_type>
float array_sum(std::vector<float_type> &vec) {
    static_assert(std::is_base_of_v<float, float_type>, "float_type must be a float");

    float_type sum = 0;
    for (float_type v : vec) {
        sum += v;
    }
    return sum;
}

template <typename float_type>
uint8_t ChanceNode<float_type>::NumChildren() {
    return this->probabilities->NumChildren();
}

template <typename float_type>
uint8_t ChanceNode<float_type>::GetRandomChildIndex() {
    return this->probabilities->GetRandomChildIndex();
}