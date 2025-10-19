//
// Created by Amir on 10/18/25.
//

#ifndef GENERICCFRLIB_INFOSET_H
#define GENERICCFRLIB_INFOSET_H
#include <array>
#include <memory>
#include <vector>


#endif //GENERICCFRLIB_INFOSET_H



template<typename float_type> class InfoSet {

    static_assert(std::is_base_of_v<float, float_type>, "float_type must be a float");

    uint8_t num_actions = 0;
    std::vector<float_type> curr_strategy;
    std::vector<float_type> cum_strategy;
    std::vector<float_type> cum_regret;

    public:

        InfoSet() = default;

        InfoSet(uint8_t num_actions);

        uint8_t NumActions();

        void Reset();

        float_type GetCurrentStrategy(int index);

        float_type GetCumulativeStrategy(int index);

        float_type GetCumulativeRegret(int index);

        void SetCurrentStrategy(int index, float_type prob);

        void SetCumulativeStrategy(int index, float_type prob);

        void SetCumulativeRegret(int index, float_type regret);

        void AddToCumulativeStrategy(int index, float_type prob);

        void AddToCumulativeRegret(int index, float_type regret);
};
