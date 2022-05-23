#include <iostream>
using namespace std;

#include "arrayqueue.h"

int main() {
    queue<int> q;
    for (int i = 0; i < 10; i++) q.enqueue(i*(i+1)); /* Random values for the sake of it */
    while (!q.isEmpty()) {
        cout << q.dequeue() << " ";
        if (!q.isEmpty()) q.enqueue(q.dequeue());
    }
}