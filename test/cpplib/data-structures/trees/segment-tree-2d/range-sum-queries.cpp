#include <cpplib/header.hpp>
#include <cpplib/data-structures/trees/segment-tree-2d.hpp>

// https://cses.fi/problemset/task/1652
int32_t main(){
    desync();
    int n, q;
    cin >> n >> q;

    vvi mat(n, vi(n));
    for(vi &i:mat){
        for(int &j:i){
            char c;
            cin >> c;
            j = (c == '*');
        }
    }

    SegTree2D<SegTreeKind::RSumQ, int> st(mat);
    while(q--){
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << st.query(y1-1, y2-1, x1-1, x2-1) << endl;
    }
    return 0;
}
