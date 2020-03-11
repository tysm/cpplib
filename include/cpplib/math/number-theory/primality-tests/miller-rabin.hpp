#pragma once
#include <cpplib/header.hpp>

using u64 = uint64_t;
using u128 = __uint128_t;

/**
 * Miller-Rabin Deterministic Test.
 *
 * Returns true when n is prime,
 * false otherwise.
 *
 * Time Complexity: O(log(n)).
 */
bool isprime(u64 n);
