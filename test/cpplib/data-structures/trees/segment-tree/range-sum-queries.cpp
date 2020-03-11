#include <cpplib/header.hpp>
#include <cpplib/data-structures/trees/segment-tree.hpp>

// https://cses.fi/problemset/task/1646
int32_t main(){
    desync();
    int n, q;
    cin >> n >> q;

    vi arr(n);
    for(int &i:arr)
        cin >> i;

    SegTree st(SegTreeKind::RSumQ, arr);
    while(q--){
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << st.query(a, b) << endl;
    }
    return 0;
}

