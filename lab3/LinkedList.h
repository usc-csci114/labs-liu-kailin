#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include <stdexcept>
#include "List.h"

template <typename T>
class Node {
	T value;
	Node* next;
};

template <typename T>
class LinkedList : public List<T> {
public:
	LinkedList();
	void append(T v);
	void insert(size_t idx, T v);
	T at(size_t idx);
	void set(size_t idx, T v);
	void remove(size_t idx);
	size_t find(T v);
	size_t size();
	bool empty();

private:

	size_t m_size;
	Node<T>* head;
	Node<T>* tail;
};

// constructor initialization
template <typename T>
LinkedList<T>::LinkedList(): m_size(0), head(nullptr), tail(nullptr) {}

// add to end of list
template <typename T>
void LinkedList<T>::append(T v)
{
    Node<T>* new_node = new Node<T>(v); // new node
    
    if (empty()) { // is this the only value
        tail = new_node;
        head = new_node;
    }
    else {
        tail -> next = new_node; // link
        tail = new_node; // assign new tail
    }
    m_size++;
}

// insert in middle of list
template <typename T>
void LinkedList<T>::insert(size_t idx, T v)
{
    if (idx > m_size){
        throw std::range_error("Out of bounds");
    }
    
    Node<T>* new_node = new Node<T>(v); // new node
    
    if(idx == 0){ // idx = 0 then value is new head
        new_node -> next = head;
        head = new_node;
        
        if (m_size == 0){ // if this the only value, the tail is also new_node
            tail = new_node;
        }
    }
    else {
        Node<T>* loc = head;
        for (size_t i = 0; i < idx; i++) { // step through list idx times
            loc = loc->next;
        }
        new_node -> next = loc -> next; // reassign next link (so it is "after" where new_node will be inserted
        if (new_node -> next == nullptr){ // if inserted at end, tail is new_node
            tail = new_node;
        }
        loc -> next = new_node; // insert new_node
    }
    m_size++;
}

// find value at index
template <typename T>
T LinkedList<T>::at(size_t idx)
{
    if (idx > m_size){
        throw std::range_error("Out of bounds");
    }
    Node<T>* loc = head;
    for (size_t i = 0; i < idx; i++) { // step through list idx times
        loc = loc->next;
    }
    return loc->value; // return value
}

// modify value
template <typename T>
void LinkedList<T>::set(size_t idx, T v)
{
    if (idx > m_size){
        throw std::range_error("Out of bounds");
    }
    Node<T>* loc = head;
    for (size_t i = 0; i < idx; i++) { // step through list idx times
        loc = loc->next;
    }
    loc->value = v; // reassign value
} 

// remove value by index
template <typename T>
void LinkedList<T>::remove(size_t idx)
{
    if (idx > m_size){
        throw std::range_error("Out of bounds");
    }
    
    Node<T>* remove_this;
    
    // reassign pointers
    if (idx == 0){
        remove_this = head; // save item to delete
        head = head -> next; // reassign head pointer
    }
    else{
        Node<T>* loc = head;
        for (size_t i = 0; i < idx; i++) { // step through list idx times
            loc = loc->next;
        }
        remove_this = loc -> next; // next bc technically returns previous to idx
        loc -> next = remove_this -> next; // next next node
        if (loc -> next == nullptr) {
            tail = loc; // reassign tail if reached end of list
        }
    }
    
    delete remove_this;
    m_size--;
}

// find index based on value
template <typename T>
size_t LinkedList<T>::find(T v)
{
    Node<T>* loc = head;
    for (size_t idx = 0; idx < m_size; idx++) { // loop through list
        if (loc -> value == v){
            return idx; // return index if found
        }
        loc = loc -> next;
    }
    return -1; // return -1 if not found
}

// return size
template <typename T>
size_t LinkedList<T>::size()
{
    return m_size;
}

// check if empty
template <typename T>
bool LinkedList<T>::empty()
{
    return m_size == 0;
}

#endif
