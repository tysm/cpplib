#include <cpplib/adt/segtree.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    SegTree<RSumQ, int> st;
    debug(st.query(0));
    st.update(0, 1);
    debug(st.query(0));
    return 0;
}
