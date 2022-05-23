#ifndef QUEUE_H
#include "arrayqueue.h"
#endif

#include <stdexcept>
using namespace std;

template <class T>
bool queue<T>::needToResize() {
    return (tail == size);
}

template <class T>
void queue<T>::resize() {
    T* temp = new T[2*size];
    for (int i = 0; i < tail - head; i++) temp[i] = data[i+head];
    data = temp;
    tail = tail - head;
    head = 0;
    size *= 2;
}

template <class T>
void queue<T>::enqueue(T obj) {
    if (needToResize()) resize();
    data[tail++] = obj;
}

template <class T>
T queue<T>::dequeue() {
    if (head == tail) throw std::out_of_range("Attempted to dequeue from an empty queue");
    return data[head++];
}

template <class T>
T queue<T>::peek() {
    if (head == tail) throw std::out_of_range("Attempted to peak from an empty queue");
    return data[head];
}

template <class T>
bool queue<T>::isEmpty() {
    return head == tail;
}