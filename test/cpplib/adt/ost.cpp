#include <cpplib/adt/ost.hpp>
#include <cpplib/stdinc.hpp>

int32_t main()
{
    ost_set<int> ost;
    ost.insert(10);
    ost.insert(*ost.find_by_order(0));
    return 0;
}
