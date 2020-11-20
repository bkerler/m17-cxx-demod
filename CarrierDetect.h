// Copyright 2020 Mobilinkd LLC.

#pragma once

#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace mobilinkd
{

template <typename FloatType, size_t N = 10>
struct CarrierDetect
{
    using result_t = std::tuple<bool, FloatType>;

    FloatType lock_;
    FloatType unlock_;
    std::array<FloatType, N> samples_;
    size_t index_ = 0;
    bool locked_ = false;

    CarrierDetect(FloatType lock_level, FloatType unlock_level)
    : lock_(lock_level), unlock_(unlock_level)
    {
        samples_.fill(0.0);
    }
    
    result_t operator()(FloatType evm)
    {
        samples_[index_++] = evm * evm;
        if (index_ == N) index_ = 0;
        
        auto rms = std::sqrt(std::accumulate(std::begin(samples_), std::end(samples_), 0.0) / N);
        if (!locked_)
        {
            if (rms < lock_) locked_ = true;
        }
        else
        {
            if (rms > unlock_) locked_ = false;
        }

        return std::make_tuple(locked_, rms);
    }
};

} // mobilinkd
