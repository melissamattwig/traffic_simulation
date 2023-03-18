#ifndef _LINKEDNODECLASS_H_
#define _LINKEDNODECLASS_H_

// Programmer: Melissa Mattwg
// Date: April 2022
// Purpose: This class creates the nodes that make up the lists. It includes
// getter functions and functions to set the pointers of the nodes. This is the
// header file and its implementation is found in LinkedNodeClass.cpp

template < class T >
class LinkedNodeClass
{
  private:
  LinkedNodeClass < T > *prevNode;
  T nodeVal;
  LinkedNodeClass < T > *nextNode;

  public:
  // A value constructor that assigns the new node with the previous pointer,
  // next pointer, and value passed in by the user
  LinkedNodeClass(LinkedNodeClass *inPrev, const T &inVal,
                  LinkedNodeClass *inNext);

  // A getter function for the value in the node
  T getValue() const;
  
  // A getter function for the next pointer in the node
  LinkedNodeClass< T >* getNext() const;
  
  // A getter function for the previous pointer in the node
  LinkedNodeClass< T >* getPrev() const;

  // Sets the next pointer in the node to be a null pointer
  void setNextPointerToNull();
  
  // Sets the previous pointer in the node to be a null pointer
  void setPreviousPointerToNull();
  
  // Sets the previous and next pointers to the current node as long as they
  // are not null
  void setBeforeAndAfterPointers();
};

#include "LinkedNodeClass.inl"
#endif