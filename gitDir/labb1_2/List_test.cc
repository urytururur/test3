
#include "List.h"

#include "catch.hpp"
#include <iostream>
using namespace std;

TEST_CASE( "Create list" )
{
    cout << 1;
    List lst{1,4,2,6,8,9};
    cout << 2;
    CHECK(lst.at(2) == 2);
    cout << 3;
    CHECK(lst.size() == 6);
    cout << 4;
    List l2;
    cout << 5;
    l2 = lst;
    cout << 6;
    CHECK(l2.size() == lst.size());
    cout << 7;
    CHECK(l2.front() == lst.front());
    cout << 8;
    CHECK(l2.back() == lst.back());
    cout << 9;
}

