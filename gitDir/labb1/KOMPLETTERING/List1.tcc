
//#include "List.h"
//#include <iterator>
#include <utility>
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

using namespace List_NS;

template<typename T>
List<T>::List()
    : head{ std::make_unique<Node>() }, tail{ new Node {} }, sz{}
{
    head->next = std::unique_ptr<Node>(tail);
    tail->prev = head.get();
}

template<typename T>
List<T>::List(List<T> const & other)
    : List<T>{}
{
    for (Node * tmp {other.head->next.get()}; tmp != other.tail ; )
    {
        push_back(tmp->value);
        tmp = tmp->next.get();
    }
}

template<typename T>
List<T>::List(List<T> && tmp) noexcept
    :List{}
{
    swap(tmp);
}

template<typename T>
List<T>::List(std::initializer_list<T> lst)
    : List<T>{}
{
    for ( auto val : lst )
    {
        push_back(val);
    }
}

template<typename T>
void List<T>::push_front(T value)
{
    std::unique_ptr<Node> tmp{std::make_unique<Node>(value, head.get(), nullptr)};
    tmp->next = std::move(head->next);
    head->next = std::move(tmp);
    head->next->next->prev = head->next.get();
    ++sz;
}

template<typename T>
void List<T>::push_back(T value)
{
    Node* old_last{tail->prev};
    old_last->next = std::make_unique<Node>(value, old_last, nullptr);
    old_last->next->next = std::make_unique<Node>(T{}, old_last->next.get(), nullptr);
    tail = old_last->next->next.get();
    ++sz;
}

template<typename T>
bool List<T>::empty() const noexcept
{
    return head->next.get() == tail;
}

template<typename T>
T & List<T>::back() const noexcept
{
    return tail->prev->value;
}

template<typename T>
T & List<T>::back() noexcept
{
    return tail->prev->value;
}

template<typename T>
T & List<T>::front() const noexcept
{
    return head->next->value;
}

template<typename T>
T & List<T>::front() noexcept
{
    return head->next->value;
}

template<typename T>
T & List<T>::at(int idx)
{
    return const_cast<T &>(static_cast<List<T> const *>(this)->at(idx));
}

template<typename T>
T const & List<T>::at(int idx) const
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

template<typename T>
int List<T>::size() const noexcept
{
    return sz;
}

template<typename T>
void List<T>::swap(List<T> & other) noexcept
{
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}

template<typename T>
List<T> & List<T>::operator=(List<T> const & rhs) &
{
    List{rhs}.swap(*this);
    return *this;
}

template<typename T>
List<T> & List<T>::operator=(List<T> && rhs)& noexcept
{
    swap(rhs);
    return *this;
}

template<typename T>
List<T>::List_Iterator::List_Iterator()
    : ptr{} {}

template<typename T>
List<T>::List_Iterator::List_Iterator(List<T>::List_Iterator const & other)
    : ptr{other.ptr}
{
    
}

template<typename T>
typename List<T>::List_Iterator List<T>::List_Iterator::operator++(int)
{
    List<T>::List_Iterator tmp{*this};

    ptr = ptr->next.get();

    return tmp;
}

template<typename T>
typename List<T>::List_Iterator& List<T>::List_Iterator::operator++()
{
    ptr = ptr->next.get();
    return *this;
}

template<typename T>
typename List<T>::List_Iterator List<T>::List_Iterator::operator--(int)
{
    List_Iterator tmp{ *this };

    ptr = ptr->prev;

    return tmp;
}

template<typename T>
typename List<T>::List_Iterator& List<T>::List_Iterator::operator--()
{
    ptr = ptr->prev;

    return *this;
}

template<typename T>
bool List<T>::List_Iterator::operator==(List_Iterator const& right) const
{
    return ptr == right.ptr ? true : false;
}

template<typename T>
bool List<T>::List_Iterator::operator!=(List_Iterator const& right) const
{
    return !(ptr == right.ptr);
}

template<typename T>
typename List<T>::List_Iterator::reference List<T>::List_Iterator::operator*()
{
    return ptr->value;
}

template<class T>
typename List<T>::Node* List<T>::List_Iterator::operator->()
{
    return ptr; // retValue == ptr-> ????
}

template<typename T>
typename List<T>::List_Iterator List<T>::end() const
{
    List_Iterator it{};
    it.ptr = tail;
    return it;
}

template<typename T>
typename List<T>::List_Iterator List<T>::begin() const
{
    List_Iterator it{};
    it.ptr = head->next.get();
    return it;
}