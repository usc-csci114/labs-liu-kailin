#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__
#include <stdexcept>
#include "List.h"

template <typename T>
class ArrayList : public List<T> {
public:
	ArrayList();
	void append(T v);
	void insert(size_t idx, T v);
	T at(size_t idx);
    virtual void set(T v)=0;
	void set(size_t idx, T v);
	void remove(size_t idx);
	size_t find(T v);
	size_t size();
	bool empty();

private:
	void resize(); //double the size of the array and copy the items
	size_t capacity;
	size_t current_size;
	T* data;
};


// constructor
template <typename T>
ArrayList<T>::ArrayList(): capacity(10), current_size(0) // set initial size
{
    data = new T[capacity]; // allocate new array
}


// add to end of array
template <typename T>
void ArrayList<T>::append(T v)
{
    if (current_size == capacity) { // check capacity
        resize();
    }
    
    data[current_size+1] = v; // add value

}


// insert in middle
template <typename T>
void ArrayList<T>::insert(size_t idx, T v)
{
    if (idx >= current_size || idx > capacity){ // check valid index
        throw std::range_error("Out of Bounds");
    }
    
    if (current_size == capacity) { // check capacity
        resize();
    }
    
    for(size_t i = current_size; i > idx; i--){ // shift values up by 1
        data[i] = data[i-1];
    }
    data[idx] = v; // insert value
    current_size++;
	
}


// return value at index
template <typename T>
T ArrayList<T>::at(size_t idx)
{
    if (idx >= current_size){ // check valid index
        throw std::range_error("Out of Bounds");
    }
    return data[idx];
}

// modify existing value template <typename T>

template <typename T>
void ArrayList<T>::set(size_t idx, T v)
{
    if (idx >= current_size || idx > capacity){ // check valid index
        throw std::range_error("Out of Bounds");
    }
    data[idx] = v;

}


// remove value by index
template <typename T>
void ArrayList<T>::remove(size_t idx)
{
    if (idx >= current_size || idx > capacity ){ // check valid index
        throw std::range_error("Out of Bounds");
    }
    for(size_t i = idx; i < current_size-1; i++){ // shift values down by 1
        data[i] = data[i+1];
    }
    current_size--;
}


// find location of value
template <typename T>
size_t ArrayList<T>::find(T v)
{
    for (size_t i=0; i < current_size; i++){
        if (data[i] == v){
            return i;
        }
    }
    return -1;
}


// return size of array
template <typename T>
size_t ArrayList<T>::size()
{
    return current_size;
}


// check if array is empty
template <typename T>
bool ArrayList<T>::empty()
{
    return current_size == 0; // returns true if empty
}


// double capacity of array
template <typename T>
void ArrayList<T>::resize()
{
    capacity *= 2; // double capacity
    T* resize_data = new T[capacity]; // new array
    
    for(size_t i=0; i < current_size; i++){ // copy over
        resize_data[i] = data[i];
    }
    delete[] data; // delete info in old data
    data = resize_data; // reassign pointer
    
}
#endif
