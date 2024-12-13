#ifndef ALGORITHM_H_INCLUDED
#define ALGORITHM_H_INCLUDED

#include <unordered_map>

enum Algorithm {
    BUBBLE,
    INSERTION,
    QUICK,
    SELECTION,
    MERGE,
    BUBBLE_SIMD,
    SELECTION_SIMD
};

std::unordered_map<Algorithm, std::string> AlgorithmName = {
    {BUBBLE, "BUBBLE"},
    {INSERTION, "INSERTION"},
    {QUICK, "QUICK"},
    {SELECTION, "SELECTION"},
    {MERGE, "MERGE"},
    {BUBBLE_SIMD, "BUBBLE_SIMD"},
    {SELECTION_SIMD, "SELECTION_SIMD"}
};

#endif // ALGORITHM_H_INCLUDED
