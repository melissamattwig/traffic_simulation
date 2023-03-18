#ifndef _FIFOQUEUECLASS_H_
#define _FIFOQUEUECLASS_H_

#include "LinkedNodeClass.h"

// Programmer: Melissa Mattwg
// Date: April 2022
// Purpose: This class creates a first in, first out queue class and includes
// functions that clear the queue, adds a node to the front of the queue,
// removes a node from the front of the queue, prints all the nodes in the
// queue, and provides the numbers of nodes in the queue. This is a header file
// and its implmentation is found in FIFOQueueClass.cpp

template < class T >
class FIFOQueueClass
{
  private:
  LinkedNodeClass < T > *head;
  LinkedNodeClass < T > *tail;

  public:
  // Default constructor that initializes a queue to be an empty, null queue
  FIFOQueueClass();

  // Destructor that destroys a queue and ensures all the dynamically allocated
  // memory is freed
  ~FIFOQueueClass();

  // Inserts the value of newItem into a new node at the back of the queue
  void enqueue(const T &newItem);

  // Takes the next (first) node out of the queue. If the queue is empty, this
  // returns false. If there is a value in the front of the queue, returns true
  // and passes the value of the removed node to outItem
  bool dequeue(T &outItem);

  // Prints the values of the nodes in the queue
  void print() const;

  // Returns the number of nodes contained in a queue
  int getNumElems() const;
  
  // Clears the nodes in the queue so it becomes an empty, null queue
  void clear();
};

#include "FIFOQueueClass.inl"
#endif