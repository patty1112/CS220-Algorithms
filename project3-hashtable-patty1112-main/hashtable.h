/*
 * hashtable.h
 *
 * A basic hashtable implementation.
 * 
 * Author: Patrick Maes
 */

#ifndef _HASHTABLE_PROJECT_H
#define _HASHTABLE_PROJECT_H

#include <functional>   // for std::hash
#include <list>         // for collision chains
#include <vector>


using namespace std;

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable();
    hashtable(int);

    // basic hashset operations
    void insert(const T& key);
    void remove(const T& key);
    bool contains(const T& key);
    typename list<T>::iterator location(const T& key);
    size_t size();
   

    // diagnostic functions
    double load_factor();
    void printHashTable();

    // convenience method, invokes the "hash" template parameter
    // function object to get a hash code
    static size_t hash(const T &key) {
        H h;
        return h(key);
    }

private:
    vector<list<T>> table;
    size_t capacity;
    size_t tableSize;
};

template <class T, class H>
hashtable<T,H>::hashtable() {
    capacity = 4;
    tableSize = 0;
    vector<list<T>> newVector(capacity);
    for(size_t i = 0; i < capacity; i++) {
        list<T> colisionList;
        newVector[i] = colisionList;
    }
    table = newVector;
}

template <class T, class H>
hashtable<T,H>::hashtable(int initial) {
    capacity = initial;
    tableSize = 0;
    vector<list<T>> newVector(capacity);
    for(size_t i = 0; i < capacity; i++) {
        list<T> colisionList;
        newVector[i] = colisionList;
    }
    table = newVector;
}

template <class T, class H>
double hashtable<T,H>::load_factor() {
    return double(tableSize) / capacity;
}

template <class T, class H>
size_t hashtable<T,H>::size() {
    return tableSize;
}

template <class T, class H>
bool hashtable<T,H>::contains(const T& VALUE) {
    int hashedVal = this->hash(VALUE);
    int index = hashedVal % capacity;
    if(table[index].size() == 0) {
        return false;
    }
    for(typename list<T>::iterator p1 = table[index].begin(); p1 != table[index].end(); p1++) {
        if(*p1 == VALUE) {
            return true;
        }
    }
    return false;
}

template <class T, class H>
void hashtable<T,H>::insert(const T& key) {
    if(this->contains(key) == true) {
        return;
    } else if ((double(tableSize + 1) / capacity) > .75) {
        vector<list<T>> newTable(capacity*2);       //Create new vector
        capacity = capacity*2;                      //Double capacity
        for(size_t i = 0; i < capacity; i++) {         //Initialize newTable with empty lists
        list<T> colisionList;
        newTable[i] = colisionList;
        }
        for(size_t i = 0; i < capacity/2; i++) {
            if(table[i].size() < 1) {
                continue;
            }
            for(typename list<T>::iterator p1 = table[i].begin(); p1 != table[i].end(); p1++) {
                int hashedValue = this->hash(*p1);
                int index = hashedValue % capacity;
                (newTable)[index].push_back(*p1);
            }
        }
        table = newTable;
        int hashedValue = this->hash(key);
        int index = hashedValue % capacity;
        (table)[index].push_back(key);
        tableSize++;
    } else {
        int hashedValue = this->hash(key);
        int index = hashedValue % capacity;
        (table)[index].push_back(key);
        tableSize++;
    }

}

template <class T, class H>
void hashtable<T,H>::remove(const T& key) {
    typename list<T>::iterator keyLocation = this->location(key);
    int hashedVal = this->hash(key);
    int index = hashedVal % capacity;
    if(keyLocation == this->table[index].end()) {
        return;
    }
    table[index].erase(keyLocation);
    tableSize--;
    return;

}

template <class T, class H>
void hashtable<T,H>::printHashTable() {
    for(size_t i = 0; i < table.size(); i++) {
        if(table[i].size() == 0) {
        continue;
        }
        for(typename list<T>::iterator p1 = table[i].begin(); p1 != table[i].end(); p1++) {
            cout << *p1 << " ";
        }
    }
}
template <class T, class H>
typename list<T>::iterator hashtable<T,H>::location(const T& VALUE) {
    int hashedVal = this->hash(VALUE);
    int index = hashedVal % capacity;
    if(table[index].size() == 0) {
        return table[index].end();
    }
    for(typename list<T>::iterator p1 = table[index].begin(); p1 != table[index].end(); p1++) {
        if(*p1 == VALUE) {
            return p1;
        }
    }
    return table[index].end();
}
#endif
