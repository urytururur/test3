
#include "List.h"
#include "catch.hpp"
#include <iostream>
#include <string>

namespace EmptyList
{
    class List
    {

    };
}

TEST_CASE( "emptyListClass" )
{
    EmptyList::List emptyListClass{};
	List_NS::List<int> blablabla{};
}

TEST_CASE( "Create list int" )
{
    List_NS::List<int> lst{1,4,2,6,8,9};
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List_NS::List<int> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

TEST_CASE("Operator= int")
{
    List_NS::List<int> lst{ 1,4,2 };
    List_NS::List<int> l2;
    l2 = lst;
    CHECK(lst.at(0) == 1);
    CHECK(lst.at(1) == 4);
    CHECK(lst.at(2) == 2);
    CHECK(l2.at(0) == 1);
    CHECK(l2.at(1) == 4);
    CHECK(l2.at(2) == 2);
}

TEST_CASE( "Push Front int" )
{
    List_NS::List<int> lst{ 1,4,7,2 };
    lst.push_front(2);
    CHECK(lst.at(1) == 1);
}

TEST_CASE( "Swap int" )
{
    List_NS::List<int> lst{ 1,2,3 };
    List_NS::List<int> lst2{ 4,5,6 };
    lst.swap(lst2);
    CHECK(lst.at(0) == 4);
    CHECK(lst.at(1) == 5);
    CHECK(lst.at(2) == 6);
    CHECK(lst2.at(0) == 1);
    CHECK(lst2.at(1) == 2);
    CHECK(lst2.at(2) == 3);
}

TEST_CASE("Empty int")
{
    List_NS::List<int> lst{};
    CHECK(lst.empty());
    lst.push_back(5);
    CHECK_FALSE(lst.empty());
}

TEST_CASE("Iterator int")
{
    List_NS::List<int> lst{ 5,2,7,4 };
    
    auto rb{ std::make_reverse_iterator(lst.end()) };
    auto re{ std::make_reverse_iterator(lst.begin()) };
    for (auto it = rb; it != re; ++it)
    {
        std::cout << *it << ' ';
    }
    
    
}

TEST_CASE( "Create list double" )
{
    List_NS::List<double> lst{1.1, 2.1, 3.1};
    CHECK(lst.at(2) == 3.1);
    CHECK(lst.size() == 3);
    List_NS::List<double> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

TEST_CASE("Operator= double")
{
    List_NS::List<double> lst{ 1.1,4.1,2.1 };
    List_NS::List<double> l2;
    l2 = lst;
    CHECK(lst.at(0) == 1.1);
    CHECK(lst.at(1) == 4.1);
    CHECK(lst.at(2) == 2.1);
    CHECK(l2.at(0) == 1.1);
    CHECK(l2.at(1) == 4.1);
    CHECK(l2.at(2) == 2.1);
}

TEST_CASE( "Push Front double" )
{
    List_NS::List<double> lst{ 1.1,4.1,7.1,2.1 };
    lst.push_front(2.1);
    CHECK(lst.at(1) == 1.1);
}

TEST_CASE( "Swap double" )
{
    List_NS::List<double> lst{ 1.1,2.1,3.1 };
    List_NS::List<double> lst2{ 4.1,5.1,6.1 };
    lst.swap(lst2);
    CHECK(lst.at(0) == 4.1);
    CHECK(lst.at(1) == 5.1);
    CHECK(lst.at(2) == 6.1);
    CHECK(lst2.at(0) == 1.1);
    CHECK(lst2.at(1) == 2.1);
    CHECK(lst2.at(2) == 3.1);
}

TEST_CASE("Empty double")
{
    List_NS::List<double> lst{};
    CHECK(lst.empty());
    lst.push_back(5.1);
    CHECK_FALSE(lst.empty());
}

TEST_CASE("Iterator double")
{
    List_NS::List<double> lst{ 2.1,3.1,1.1,58.1,0.1,3.1,4.1,6.1 };
    
    auto rb{ std::make_reverse_iterator(lst.end()) };
    auto re{ std::make_reverse_iterator(lst.begin()) };
    for (auto it = rb; it != re; ++it)
    {
        std::cout << *it << ' ';
    }   
}

//TEST CASE STRING

TEST_CASE( "Create list string" )
{
    List_NS::List<std::string> lst{"hej","på","dig"};
    CHECK(lst.at(2) == "dig");
    CHECK(lst.size() == 3);
    List_NS::List<std::string> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

TEST_CASE("Operator= string")
{
    List_NS::List<std::string> lst{ "hej","på","dig" };
    List_NS::List<std::string> l2;
    l2 = lst;
    CHECK(lst.at(0) == "hej");
    CHECK(lst.at(1) == "på");
    CHECK(lst.at(2) == "dig");
    CHECK(l2.at(0) == "hej");
    CHECK(l2.at(1) == "på");
    CHECK(l2.at(2) == "dig");
}

TEST_CASE( "Push Front string" )
{
    List_NS::List<std::string> lst{ "hej","på","dig", "du" };
    lst.push_front("hallå");
    CHECK(lst.at(1) == "hej");
}

TEST_CASE( "Swap string" )
{
    List_NS::List<std::string> lst{ "hallå", "på", "mig" };
    List_NS::List<std::string> lst2{ "mig", "på", "hallå", "du" };
    lst.swap(lst2);
    CHECK(lst.at(0) == "mig");
    CHECK(lst.at(1) == "på");
    CHECK(lst.at(2) == "hallå");
    CHECK(lst.at(3) == "du");
    CHECK(lst2.at(0) == "hallå");
    CHECK(lst2.at(1) == "på");
    CHECK(lst2.at(2) == "mig");
}

TEST_CASE("Empty string")
{
    List_NS::List<std::string> lst{};
    CHECK(lst.empty());
    lst.push_back("du hast");
    CHECK_FALSE(lst.empty());
}

TEST_CASE("Iterator string")
{
    List_NS::List<std::string> lst{ "dig","på ","hej " };
    
    auto rb{ std::make_reverse_iterator(lst.end()) };
    auto re{ std::make_reverse_iterator(lst.begin()) };
    for (auto it = rb; it != re; ++it)
    {
        std::cout << *it << ' ';
    }
}

TEST_CASE("Piloperator string")
{
	List_NS::List<std::string> lst{ "dig","på ","hej " };
    
    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << it->value;
    }
}


TEST_CASE("Piloperator double")
{
	List_NS::List<double> lst{ 1.1,3.1 ,2.3 };
    
    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << it->value;
    }
}


TEST_CASE("Piloperator")
{
	List_NS::List<int> lst{ 1, 3, 34, 4, 6, 2 };
    
    for (auto it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << it->value;
    }
}

