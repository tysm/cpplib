#pragma once
#include <cpplib/stdinc.hpp>

template<typename T, size_t N, size_t M = N>
struct matrix
{
    static_assert(N > 0 and M > 0, "can't create empty matrix.");

    array<array<T, M>, N> mat;

    matrix() {}

    template<typename T1>
    matrix(const T1 &value)
    {
        fill(value);
    }

    void fill(const T &value)
    {
        for(uint i = 0; i < N; ++i)
            mat[i].fill(value);
    }

    size_t size() const
    {
        return mat.size();
    }

    array<T, M> &operator[](const size_t pos)
    {
        return mat[pos];
    }

    const array<T, M> &operator[](const size_t pos) const
    {
        return mat[pos];
    }

    matrix &operator+=(const matrix &rhs)
    {
        for(uint i = 0; i < N; ++i) {
            for(uint j = 0; j < M; ++j)
                mat[i][j] += rhs[i][j];
        }
        return *this;
    }

    matrix &operator-=(const matrix &rhs)
    {
        for(uint i = 0; i < N; ++i) {
            for(uint j = 0; j < M; ++j)
                mat[i][j] -= rhs[i][j];
        }
        return *this;
    }

    friend matrix operator+(matrix lhs, const matrix &rhs)
    {
        return lhs += rhs;
    }

    friend matrix operator-(matrix lhs, const matrix &rhs)
    {
        return lhs -= rhs;
    }

    template<size_t L>
    friend matrix<T, N, L> operator*(const matrix &lhs, const matrix<T, M, L> &rhs)
    {
        matrix<T, N, L> res(0);
        for(uint i = 0; i < N; ++i) {
            for(uint j = 0; j < L; ++j) {
                for(uint k = 0; k < M; ++k)
                    res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
        return res;
    }

    friend bool operator==(const matrix &lhs, const matrix &rhs)
    {
        for(uint i = 0; i < N; ++i) {
            for(uint j = 0; j < M; ++j) {
                if(lhs[i][j] != rhs[i][j])
                    return false;
            }
        }
        return true;
    }

    friend bool operator!=(const matrix &lhs, const matrix &rhs)
    {
        return !(lhs == rhs);
    }

    friend matrix exp(matrix b, uint e)
    {
        static_assert(N == M, "only n by n can be exponentied.");
        matrix<T, N> res = matrix<T, N>::identity();
        for(; e > 0; e >>= 1) {
            if(e & 1)
                res = res * b;
            b = b * b;
        }
        return res;
    }

    friend ostream &operator<<(ostream &lhs, const matrix &rhs)
    {
        for(uint i = 0; i < N; ++i) {
            for(uint j = 0; j < M; ++j)
                lhs << rhs[i][j] << " \n"[j == M - 1 and i != N - 1];
        }
        return lhs;
    }

    static matrix identity()
    {
        static_assert(N == M, "only n by n matrix have identity.");
        matrix<T, N> res;
        for(uint i = 0; i < N; ++i) {
            res[i].fill(0);
            res[i][i] = 1;
        }
        return res;
    }
};

template<typename T, size_t N, size_t M = N>
using mat = matrix<T, N, M>;
