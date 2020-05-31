
#include "List.h"

#include "catch.hpp"

#include <iostream>

using namespace std;

TEST_CASE( "Create list" )
{
    List lst{1,4,2,6,8,9};
    cout << lst.size() << endl;
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

