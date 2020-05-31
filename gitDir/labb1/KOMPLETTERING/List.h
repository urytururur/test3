#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>
#include <iostream>

//TODO: back() och front() ska returnera en referens då T kan vara en
//komplex datatyp vi inte vill kopiera

//TODO: begin() och end() ska inte vara const då en användare ska
//kunna modifiera objektet som ligger på respektive begin och end på
//samma rad som anropet till funktionen. En Iterator ska även i
//allmänhet kunna ändra på objekt den itererar över.

//TODO: List_Iterator ska ligga i det publika gränssnittet. Efter ni
//åtgärdat detta, tänk på att en List_Iterator endast ska kunna skapas
//med begin() och end().
//Hint: Lägg List_Iterator konstruktorer där användaren inte kommer åt dem.

//TODO: -> ska returnera en referens till objektet som ligger i nodens
//value. Inte själva noden
/*Hint:
List_NS::List<std::string> lst{"du","hast","mich"};
for (auto it = lst.begin(); it != lst.end(); ++it)
{
std::cout << it->length() << " ";
}
Output: 3 4 4
 */
namespace List_NS
{
    template<typename T>
    class List
    {
    public:
        List();
        List(List<T> const &);
        List(List<T> &&) noexcept;
        List(std::initializer_list<T>);

        List<T> &operator=(List<T> const &) &;;
        List<T> & operator=(List<T> &&)& noexcept;

        void push_front(T);
        void push_back(T);

        T& back() const noexcept;
        T& back() noexcept;

        T& front() const noexcept;
        T& front() noexcept;

        T& at(int idx);
        T const & at(int idx) const;

        int size() const noexcept;
        bool empty() const noexcept;

        void swap(List & other) noexcept;



    private:
        struct Node
        {
            Node() = default;
            Node(T v, Node* p, Node* n)
                : value{v}, prev{p}, next{std::unique_ptr<Node>(n)} {}
            T value {};
            Node * prev {};
            std::unique_ptr<Node> next {};
        };
        std::unique_ptr<Node> head;
        Node* tail;
        int sz {};

        class List_Iterator
        {
        public:

            List_Iterator();
            List_Iterator(List_Iterator const & other);

            typedef std::bidirectional_iterator_tag iterator_category;
            typedef T value_type;
            typedef int difference_type;
            typedef value_type* pointer;
            typedef value_type& reference;

            Node* ptr{};

            List_Iterator operator++(int);
            List_Iterator operator--(int);
            List_Iterator& operator++();
            List_Iterator& operator--();

            bool operator==(List_Iterator const& rhs) const;
            bool operator!=(List_Iterator const& rhs) const;

            reference operator*();
            Node* operator->();

        private:
        };

        public:
        List_Iterator end() const;
        List_Iterator begin() const;

        friend std::ostream& operator<<(std::ostream& lhs, typename List<T>::Node const& rhs)
        {
            lhs << rhs.value;
            return lhs;
        }
    };

    #include "List1.tcc"
}



#endif //LIST_H

























/*

//#include "List.h"
//#include <iterator>
#include <utility>
#include <stdexcept>
//#include <iostream>

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
    head->next = std::make_unique<Node>(value, head.get(), nullptr);
    head->next->next = std::make_unique<Node>(T{}, head->next.get(), nullptr);
    tail = head->next->next.get();
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
T List<T>::back() const noexcept
{
    return tail->prev->value;
}

template<typename T>
T & List<T>::back() noexcept
{
    return tail->prev->value;
}

template<typename T>
T List<T>::front() const noexcept
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
typename List<T>::List_Iterator List<T>::List_Iterator::operator++()
{
    ptr = ptr->next.get();

    List_Iterator tmp{ *this };

    return tmp;
}

template<typename T>
typename List<T>::List_Iterator List<T>::List_Iterator::operator--(int)
{
    List_Iterator tmp{ *this };

    ptr = ptr->prev;

    return tmp;
}

template<typename T>
typename List<T>::List_Iterator List<T>::List_Iterator::operator--()
{
    ptr = ptr->prev;

    List_Iterator tmp{ *this };

    return tmp;
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
    return *ptr;
}


#endif //LIST_H
*/
