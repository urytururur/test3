#include "List.h"
#include <iterator>
#include <utility>
#include <stdexcept>
#include <iostream>

/*
struct List::Node
{
    Node() = default;
    Node(int v, Node* p, Node* n)
        : value{v}, prev{p}, next{std::unique_ptr<Node>(n)} {}
    int value {};
    Node * prev {};
    std::unique_ptr<Node> next {};
};
*/

/*List::List()
    : head{ new Node{} }, tail{}, sz{}
{
    head->next = new Node{0, head.get(), nullptr};
    tail = std::make_unique<Node>(0,head->next,nullptr);
}*/

List::List()
    : head{ std::make_unique<Node>() }, tail{ new Node {} }, sz{}
{
    head->next = std::unique_ptr<Node>(tail);
    tail->prev = head.get();
}

List::~List()
{
  /*while(tail != nullptr)
  {
    Node* tmp = tail.get();
    tail = tail->prev;
    delete tmp;
  }*/
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
    Node * old_first { head->next.get() };
    std::cout << 20;
    head->next = std::unique_ptr<Node>(new Node{ value, head.get(), old_first });
    std::cout << 30;
    old_first->prev = head->next.get();
    std::cout << 40;
    ++sz;
}

/*
void List::push_back(int value)
{
    Node * old_last { tail->prev };

    std::unique_ptr<Node> tmp{std::move(old_last->next)};
    old_last->next = std::unique_ptr<Node>(std::make_unique<Node>(value, old_last, nullptr));
    old_last->next->next = std::move(tmp);

    //old_last->next = std::unique_ptr<Node>(new Node{ value, old_last, tail });
    tail->prev = old_last->next.get();
    ++sz;
}
*/

/*void List::push_back(int value)
{
    Node * old_last { tail->prev };
    std::unique_ptr<Node> tmp{ std::move(old_last->next) };
    old_last->next = std::make_unique<Node>(value, old_last, std::move(tmp).get());
    tail->prev = old_last->next.get();
    ++sz;
}*/

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
