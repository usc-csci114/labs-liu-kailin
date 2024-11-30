#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <utility>
#include <vector>
#include <map>
#include <stdexcept>
#include <utility>
#include <iostream>

template <typename K, typename V>
class HashTable {
public:
	HashTable();
	~HashTable();
	void insert(K key, V value);
	V find(K key);
	void remove(K key);
	size_t size();
	bool empty();
	
private:
	std::vector< std::map<K,V> > table;
	void resize();
	size_t size_;
	size_t alpha;
	uint64_t hash(K key);
};

template <typename K, typename V>
HashTable<K,V>::HashTable() { table.resize(1); alpha = 1; size_ = 0;};

template <typename K, typename V>
HashTable<K,V>::~HashTable() {};

template <typename K, typename V>
uint64_t HashTable<K,V>::hash(K key)
{
	std::hash<K> hasher;
	return hasher(key);
}

template <typename K, typename V>
void HashTable<K,V>::insert(K key, V value)
{
    if ((size_+1)/table.size() > alpha) {
        resize();
    }
    
    size_t idx = hash(key) % table.size();
    
    table[idx][key] = value;
    // table[idx].insert(std::pair<k,v>(key,value));
    size_++;
    
}

template <typename K, typename V>
V HashTable<K,V>::find(K key)
{
    size_t idx = hash(key) % table.size();
    if(table[idx].count(key) > 0){
        return table[idx][key];
    }
    else {
        throw std::range_error("Key not found.");
    }
}

template <typename K, typename V>
void HashTable<K,V>::remove(K key)
{
    size_t idx = hash(key) % table.size();
        if(table[idx].count(key) > 0 )
        {
            table[idx].erase(key);
            size_--;
        }
        else {
            throw std::range_error("Key not found.");
        }
}

template <typename K, typename V>
size_t HashTable<K,V>::size()
{
    return size_;
}

template <typename K, typename V>
bool HashTable<K,V>::empty()
{
    if (size() = 0){
        return true;
    }
}

template <typename K, typename V>
void HashTable<K,V>::resize()
{
	std::cout << "resizing " << table.size() << " -> " << table.size()*2 << std::endl;
    
    // copy into old_table
    std::vector<std::map<K, V>> old_table = table;
    
    // resize table to zero and then double based on old_table size
    table.clear();
    size_ = 0
    table.resize(2 * old_table.size());
    
    //loop through old_table
    for (size_t idx = 0; idx < old_table.size(); idx++) {
        // pull map
        std::map<K, V>& map = old_table[idx];
        // set iterator
        typename std::map<K, V>::iterator it;
        // loop iterator to insert all entries, update size_
        for (it = map.begin(); it != map.end(); it++) {
            insert(it->first, it->second);
            size_++;
        }
    }
    
    // map<key,value>:: iterator it = m.begin()
    // it -> first
    // it -> second
}
#endif
