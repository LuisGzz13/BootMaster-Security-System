#ifndef STACK2_H
#define STACK2_H
#include "node.h"

template <class T> class stack2 {
private:
  node<T> *top;
  int size;

public:
  stack2();
  ~stack2();
  void push(T);
  void pop();
  T Top();
  bool isFull();
  bool isEmpty();
};

template <class T> stack2<T>::stack2() {
  top = NULL;
  size = 0;
}

template <class T> stack2<T>::~stack2() {
  node<T> *next;
  next = top->getNext();
  while (top != NULL) {
    delete top;
    top = next;
  }
}

template <class T> void stack2<T>::push(T data) {
  node<T> *newNode;
  newNode = new node<T>(data, top);
  top = newNode;
  size++;
}

template <class T> void stack2<T>::pop() {
  node<T> *next;
  next = top->getNext();
  delete top;
  top = next;
  size--;
}

template <class T> T stack2<T>::Top() { return top->getData(); }

template <class T> bool stack2<T>::isFull() { return false; }

template <class T> bool stack2<T>::isEmpty() { return size == 0; }

#endif