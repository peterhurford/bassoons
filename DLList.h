/*
 * DLList.h
 *
 *  Created on: Apr 24, 2014
 *      Author: Peter and Bryan
 */

#ifndef DLLIST_H_
#define DLLIST_H_

#include <iostream>
#include <string>
#include <cstdlib>

template <typename T>
class Node;

template <typename T>
class DLList;

template <typename T>
std::ostream& operator<<(std::ostream& os, const DLList<T>& l);

template <typename T>
class Node {
  friend class DLList<T>;
public:
  Node<T>(T item = 0, Node<T> * next = NULL, Node<T> * prev = NULL)
    : item_(item), next_(next), prev_(prev) {}
private:
  T item_;
  Node<T> * next_;
  Node<T> * prev_;
};

template <typename T>
class DLList {
public:
  // Constructors

  DLList<T>()
    : head(NULL), tail(NULL), nextiter(NULL), size(0) {}
  DLList<T>(const DLList<T>& from);

  // Destructor

  virtual ~DLList<T>();

  // Member functions

  DLList<T>& operator=(const DLList<T>& from);
  int length() const { return size; } 
  void append(const T& item);
  void insert(int index, const T& item);
  T pop(int index=-1);
  T& operator[](int index);
  std::string str() const;
  void resetForward() { nextiter = NULL; }	
  T next();

private:
  Node<T> * head;
  Node<T> * tail;
  Node<T> * nextiter;
  int size;

  void allocCopy(const DLList<T>& from);
  void dealloc();
  Node<T> * _find(int index);
  T _delete(int index);


  // Non-member friends
  friend std::ostream& operator<< <T>(std::ostream& os, const DLList& l);
};

// Auxiliary classes for throwing "exceptions" on violated preconditions
class IndexError { };
class StopIteration { };

// Non-member function prototype for users of class
template <typename T>
std::ostream& operator<<(std::ostream& os, const DLList<T>& l);

#include "DLList.hpp"
#endif /* DLLIST_H_ */
