#ifndef _SORTEDLISTCLASS_H_
#define _SORTEDLISTCLASS_H_

#include "LinkedNodeClass.h"

// Programmer: Melissa Mattwg
// Date: April 2022
// Purpose: This class creates a doubly linked sorted list. It includes
// functions to insert nodes into the list, clear the list, print the list
// from the front and the back, remove nodes from the front and back, get the
// number of total elements in the list as well as the value of a specific
// node in the list. This is the header file for the implementation found in
// SortedListClass.cpp

template <class T>
class SortedListClass
{
  private:
  LinkedNodeClass < T > *head;
  LinkedNodeClass < T > *tail;

  public:
  // A default constructor that creates and empty list
  SortedListClass();

  // A copy constructor that makes a deep copy using a passed in list
  SortedListClass(const SortedListClass &rhs);

  // a destrcutor that empties the list to be a null list
  ~SortedListClass();
  
  // Similar to the destructor, this function clears the list to make it an 
  // empty list that is null
  void clear();

  // Inserts a value into the list using a passed in value
  void insertValue(const T &valtoInsert);
  
  // Prints the list starting from the first node to the last
  void printForward() const;
  
  // Prints the list starting from the last node to the first 
  void printBackward() const;

  // Removes the first value in the front of the list. Returns true if a value
  // was removed and passes the value that is removed as theVal
  bool removeFront(T &theVal);

  // Removes the last value in the back of the list. Returns true if a value
  // was removed and passes the value that is removed as theVal
  bool removeLast(T &theVal);
  
  // Returns the number of nodes in a list
  int getNumElems() const;
   
  // Provides the value, passed through outVal, at the index provided by the
  // passed in index parameter, and returns true. Otherwise returns false if
  // the index provided is out of range
  bool getElemAtIndex(const int index, T &outVal) const;
};

#include "SortedListClass.inl"
#endif