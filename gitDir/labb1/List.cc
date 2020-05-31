#include "List.h"
#include <iterator>
#include <utility>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

/*
struct List::Node
{
    Node() = default;
    Node(int v, Node* p, Node* n)
        : value{v}, prev{p}, next{n} {}
    int value {};
    Node * prev {};
    Node * next {};
};
*/

List::List()
    : head{std::make_unique<Node>(0, nullptr, nullptr)}, tail{new Node(0, head.get(), nullptr)}, sz{}
{
    head->next = std::unique_ptr<Node>(tail);
    tail->prev = head.get();
}

List::List(List const & other)
    : List{}
{
    for (Node * tmp {other.head->next.get()}; tmp != other.tail ; )
    {
        push_back(tmp->value);
        tmp = tmp->next.get();
    }
}
List::List(List && tmp) noexcept
    :List{}
{
    swap(tmp);
}

List::List(std::initializer_list<int> lst)
    : List{}
{
    for ( auto val : lst )
    {
        push_back(val);
    }
}

void List::push_front(int value)
{
    head->next = std::make_unique<Node>(value, head.get(), nullptr);
    head->next->next = std::make_unique<Node>(0, head->next.get(), nullptr);
    tail = head->next->next.get();
    ++sz;
}

void List::push_back(int value)
{
    Node* old_last{tail->prev};
    old_last->next = std::make_unique<Node>(value, old_last, nullptr);
    old_last->next->next = std::make_unique<Node>(0, old_last->next.get(), nullptr);
    tail = old_last->next->next.get();
    ++sz;
}

bool List::empty() const noexcept
{
    return head->next.get() == tail;
}

int List::back() const noexcept
{
    return tail->prev->value;
}
int & List::back() noexcept
{
    return tail->prev->value;
}

int List::front() const noexcept
{
    return head->next->value;
}
int & List::front() noexcept
{
    return head->next->value;
}

int & List::at(int idx)
{
    return const_cast<int &>(static_cast<List const *>(this)->at(idx));
}

int const & List::at(int idx) const
{
    if (idx >= sz)
        throw std::out_of_range{"Index not found"};
    Node * tmp {head->next.get()};
    while ( idx > 0 )
    {
        tmp = tmp->next.get();
        --idx;
    }
    return tmp->value;
}

int List::size() const noexcept
{
    return sz;
}

void List::swap(List & other) noexcept
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}

List & List::operator=(List const & rhs) &
{
    List{rhs}.swap(*this);
    return *this;
}

List & List::operator=(List && rhs)& noexcept
{
    swap(rhs);
    return *this;
}
