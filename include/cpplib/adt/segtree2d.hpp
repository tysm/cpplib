#pragma once
#include <cpplib/adt/segtree.hpp>
#include <cpplib/adt/segtree2db.hpp>
#include <cpplib/stdinc.hpp>

template<STKind K, typename T>
using SegTree2D = SegTree2DB<STNode<K, T>, T>;
