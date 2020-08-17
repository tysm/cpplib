#include <cpplib/adt/segtrees.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    SegTreeS<RSumQ, int> st;
    debug(st.query(0));
    st.update(0, 1);
    debug(st.query(0));
    st.update(0, 1);
    st.set(0, 0);
    debug(st.query(0));
    return 0;
}
