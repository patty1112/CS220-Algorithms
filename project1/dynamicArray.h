#ifndef ARRAY
#define ARRAY
#include <iostream>
using namespace std;
template <typename T>
class Array {
    private:
    T* front;
    int size;

    public:
    Array();
    Array(const int);
    Array(const Array&);
    ~Array();
    Array& operator=(const Array&);
    T get(int) const;             //Gets the value at an index.
    void set(const int, const T);
    void insert(int, const T&);
    void remove(int);
    int listSize() const;
    void print() const;
    Array* grow();
    Array* doubleSize();

    void printDimensionalArray();
};

//------------------------------ IMPLEMENTATIONS -------------------------------

template <typename T>
Array<T>::Array() {
    front = new T[1];
    *front = T();
    this->size = 1;
}

template <typename T>
Array<T>::Array(const int initialSize) {
    front = new T[initialSize];
    T* temp = front;
    for(int i = 0; i < initialSize; i++) {
        *temp = T();
        temp++;
    }
    this->size = initialSize;
}

template <typename T>
Array<T>::Array(const Array& OTHER) {
    this->size = OTHER.size;
    this->front = new T[OTHER.size];
    T* temp1 = OTHER.front;
    T* temp2 = this->front;
    for(int i = 0; i < OTHER.size; i++) {
        *temp2 = *temp1;
        temp1++;
        temp2++;
    }
}

template <typename T>
Array<T>::~Array() {
    delete[] this->front;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& OTHER) {
    if(this == &OTHER) {
        return *this;
    }
    delete[] this->front;
    this->size = OTHER.size;
    this->front = new T[OTHER.size];
    T* temp1 = OTHER.front;
    T* temp2 = this->front;
    for(int i = 0; i < OTHER.size; i++) {
        *temp2 = *temp1;
        temp1++;
        temp2++;
    }
    return *this;
}

template <typename T>
Array<T>* Array<T>::grow() {
    T* newFront = new T[this->size + 1];
    T* temp1 = this->front;
    T* temp2 = newFront;
    for(int i = 0; i < this->size; i++) {
        *temp2 = *temp1;
        temp1++;
        temp2++;
    }
    temp2++;
    *temp2 = T();
    this->size++;
    delete[] this->front;
    this->front = newFront;
    return this;
}

template <typename T>
T Array<T>::get(int INDEX) const {
    if(INDEX > (this->size - 1)) {
        INDEX = this->size - 1;
    } else if(INDEX < 0) {
        INDEX = 0;
    }
    T value;
    value = this->front[INDEX];
    return value;
}

template <typename T>
void Array<T>::set(const int INDEX, const T VALUE) {
    if(INDEX > (this->size - 1) || (INDEX < 0 && abs(INDEX) > this->size) ) {
        return;
    } else if (INDEX < 0 && abs(INDEX) <= this->size) {
        this->front[this->size - INDEX] = VALUE;
    }
    this->front[INDEX] = VALUE;
}

template <typename T>
void Array<T>::insert(int INDEX, const T& VALUE) {
    if(INDEX > (this->size)) {
        INDEX = this->size;
    } else if(INDEX < 0) {
        return;
    }
    this->grow();
    T* marker = this->front;
    marker = marker + INDEX;
    T* mover = this->front;
    mover = mover + (this->size - 1);
    T* temp = mover;
    for(int i = 0; i < ((this->size - 1) - INDEX); i++) {
        temp--;
        *mover = *temp;
        mover = temp;
    }
    *marker = VALUE;
}

template <typename T>
int Array<T>::listSize() const {
    return this->size;
}

template <typename T>
void Array<T>::print() const {
    for(int i = 0; i < this->size; i++) {
        cout << this->front[i] << " ";
    }
    cout << endl;
}

template <typename T>
void Array<T>::remove(int INDEX) {
    if(INDEX < 0) {
        return;
    } else if (INDEX >= this->size) {
        return;
    }
    T* newArray = new T[this->size - 1];
    for(int i = 0; i < (this->size); i++) {
        if(i == INDEX) {
            continue;
        }
        if(i < INDEX) {
            newArray[i] = this->front[i];
        } else if(i > INDEX) {
            newArray[i-1] = this->front[i];
        }
    }
    delete[] this->front;
    this->front = newArray;
    this->size--;
}

template <typename T>
Array<T>* Array<T>::doubleSize() {
    T* newFront = new T[this->size * 2];
    T* temp1 = this->front;
    T* temp2 = newFront;
    for(int i = 0; i < this->size; i++) {
        *temp2 = *temp1;
        temp1++;
        temp2++;
    }
    temp2++;
    *temp2 = T();
    this->size = this->size * 2;
    delete[] this->front;
    this->front = newFront;
    return this;
}
#endif