#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Random Integer.
 *
 * Generates a random integer in the range
 * [l, r].
 *
 * Time Complexity: O(?).
 * Space Complexity: O(?).
 */
int randint(const int l, const int r){
    random_device ndgen; // non-deterministic random generator.
    mt19937 dgen(ndgen()); // deterministic random generator.
    uniform_int_distribution<int> distribution(l, r);
    return distribution(dgen);
}

/**
 * Random UInteger16.
 *
 * Generates a random integer in the range
 * [l, UINT16_MAX].
 *
 * Time Complexity: O(?).
 * Space Complexity: O(?).
 */
int randuint16(const uint16_t l = 0){
    return randint(l, UINT16_MAX);
}
