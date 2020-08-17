#include <cpplib/adt/segtree2d.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    SegTree2D<RSumQ, int> st;
    debug(st.query(0, 0));
    st.update(0, 0, 1);
    debug(st.query(0, 0));
    return 0;
}
