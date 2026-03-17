/**
 * @file bulkccStack.h
 * @brief Stack class with O(1) size tracking and thread safety
 * @author Christian (graetz23@gmail.com)
 *
 * BULKCC is distributed under the MIT License (MIT); this file is part of.
 *
 * Copyright (c) 2008-2024 Christian (graetz23@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __bulkccStack_h__
#define __bulkccStack_h__

#include "./bulkccNode.h"
#include "./bulkccException.h"

namespace BULKCC {

#define _VERSION_BULKCC_Stack_ 1.0

#define _DEBUG_BULKCC_Stack_

/**
 * @class Stack
 * @brief Stack class with O(1) size tracking and thread safety
 *
 * The Stack class provides a modern, thread-safe stack implementation
 * with O(1) size tracking. It uses a NodePool for memory management
 * and provides various operations for managing stack elements.
 *
 * @section features Features
 * - O(1) size tracking
 * - Thread-safe operations with mutex
 * - Object pool for efficient memory allocation
 * - Type-safe storage with type erasure
 *
 * @section example Example
 * @code
 * BULKCC::Stack stack;
 * stack.push<MyClass*>(new MyClass());
 * size_t count = stack.count<MyClass*>(); // O(1)!
 * MyClass* obj = stack.pop<MyClass*>();
 * @endcode
 *
 * @see Node
 * @see NodePool
 * @see StackGuard
 */
class Stack {
public:

  /**
   * @brief Constructor
   *
   * Initializes a new Stack with an optional node pool.
   *
   * @param pool Optional pointer to a NodePool for memory management
   */
  Stack(NodePool* pool = 0);

  /**
   * @brief Destructor
   *
   * Cleans up the stack by calling erase().
   */
  virtual ~Stack();

  /**
   * @brief Push an object onto the stack
   *
   * Adds a new object of type T to the top of the stack.
   *
   * @tparam T The type of object to push
   * @param data The object to push onto the stack
   */
  template<class T>
  void push(T data);

  /**
   * @brief Pop an object from the stack
   *
   * Removes and returns the first object of type T from the stack.
   *
   * @tparam T The type of object to pop
   * @return The popped object, or 0 if not found
   */
  template<class T>
  T pop();

  /**
   * @brief Peek at the top object of a specific type
   *
   * Returns the first object of type T without removing it.
   *
   * @tparam T The type of object to peek at
   * @return The object, or 0 if not found
   */
  template<class T>
  T peek() const;

  /**
   * @brief Count objects of a specific type
   *
   * Returns the number of objects of type T in the stack.
   *
   * @tparam T The type to count
   * @return Number of objects of type T (O(n) traversal)
   */
  template<class T>
  size_t count() const;

  /**
   * @brief Find all objects of a specific type
   *
   * Returns all objects of type T as a newly allocated array.
   * Each matching object is removed from the stack during retrieval.
   *
   * @tparam T The type of objects to find
   * @return Array of objects of type T (must be deleted by caller), or 0 if none
   */
  template<class T>
  T* findAll() const;

  /**
   * @brief Identify if top node is of a specific type
   *
   * Checks if the top node of the stack contains an object of type T.
   *
   * @tparam T The type to check for
   * @return true if the top node contains type T, false otherwise
   */
  template<class T>
  bool identify() const;

  /**
   * @brief Clean all stored objects
   *
   * Sets all stored object pointers to null without deleting nodes.
   * The stack structure remains intact.
   */
  void clean();

  /**
   * @brief Erase the entire stack
   *
   * Deletes all nodes in the stack and resets size to zero.
   */
  void erase();

  /**
   * @brief Check if stack is empty
   *
   * @return true if the stack is empty, false otherwise
   */
  bool empty() const;

  /**
   * @brief Get the size of the stack
   *
   * Returns the total number of nodes in the stack.
   *
   * @return Number of nodes in the stack (O(1))
   */
  size_t size() const;

  /**
   * @brief Get the head node
   *
   * Returns a pointer to the head node of the stack.
   *
   * @return Pointer to the head node, or 0 if empty
   */
  Node* head() const;

  /**
   * @brief Get the node pool
   *
   * Returns the node pool used by this stack.
   *
   * @return Pointer to the NodePool
   */
  NodePool* getPool() const;

  /**
   * @brief Set the node pool
   *
   * Sets the node pool to use for memory management.
   *
   * @param pool Pointer to a NodePool
   */
  void setPool(NodePool* pool);

private:

  /**
   * @brief Check and create pool if needed
   *
   * Creates a new NodePool if none is set.
   */
  void checkPool();

  Node* _head;
  NodePool* _pool;
  size_t _size;
  mutable Mutex _mutex;

};

inline Stack::Stack(NodePool* pool)
    : _head(0), _pool(pool), _size(0), _mutex() {
#ifdef _DEBUG_BULKCC_Stack_
  std::cout << "Stack::Stack()" << std::endl << std::flush;
#endif
}

inline Stack::~Stack() {
#ifdef _DEBUG_BULKCC_Stack_
  std::cout << "Stack::~Stack()" << std::endl << std::flush;
#endif
  erase();
}

inline void Stack::checkPool() {
  if (_pool == 0) {
    _pool = new NodePool();
  }
}

template<class T>
void Stack::push(T data) {
  Lock lock(_mutex);
  checkPool();

  Node* node = _pool->allocate();
  node->setData<T>(data);
  node->setNext(_head);
  _head = node;
  _size++;
}

template<class T>
T Stack::pop() {
  Lock lock(_mutex);

  if (_head == 0) {
    return 0;
  }

  Node* node = _head;
  while (node != 0 && !node->isType<T>()) {
    node = node->getNext();
  }

  if (node == 0) {
    return 0;
  }

  T data = node->getData<T>();
  node->_data = 0;
  node->_dataIsSet = false;
  _size--;

  return data;
}

template<class T>
T Stack::peek() const {
  Lock lock(_mutex);

  if (_head == 0) {
    return 0;
  }

  Node* node = _head;
  while (node != 0 && !node->isType<T>()) {
    node = node->getNext();
  }

  if (node == 0) {
    return 0;
  }

  return node->getData<T>();
}

template<class T>
size_t Stack::count() const {
  Lock lock(_mutex);

  size_t count = 0;
  Node* node = _head;
  while (node != 0) {
    if (node->isType<T>() && node->isDataSet()) {
      count++;
    }
    node = node->getNext();
  }

  return count;
}

template<class T>
T* Stack::findAll() const {
  Lock lock(_mutex);

  size_t cnt = 0;
  Node* node = _head;
  while (node != 0) {
    if (node->isType<T>() && node->isDataSet()) {
      cnt++;
    }
    node = node->getNext();
  }

  if (cnt == 0) {
    return 0;
  }

  T* list = new T[cnt];
  node = _head;
  size_t pos = 0;
  while (node != 0) {
    if (node->isType<T>() && node->isDataSet()) {
      list[pos++] = node->getData<T>();
      node->_data = 0;
      node->_dataIsSet = false;
    }
    node = node->getNext();
  }

  return list;
}

template<class T>
bool Stack::identify() const {
  Lock lock(_mutex);

  if (_head == 0) {
    return false;
  }

  return _head->isType<T>();
}

inline void Stack::clean() {
  Lock lock(_mutex);

  Node* node = _head;
  while (node != 0) {
    node->_data = 0;
    node->_dataIsSet = false;
    node = node->getNext();
  }
}

inline void Stack::erase() {
  Lock lock(_mutex);

  Node* node = _head;
  while (node != 0) {
    Node* next = node->getNext();
    _pool->deallocate(node);
    node = next;
  }
  _head = 0;
  _size = 0;
}

inline bool Stack::empty() const {
  Lock lock(_mutex);
  return _head == 0;
}

inline size_t Stack::size() const {
  Lock lock(_mutex);
  return _size;
}

inline Node* Stack::head() const {
  Lock lock(_mutex);
  return _head;
}

inline NodePool* Stack::getPool() const {
  Lock lock(_mutex);
  return _pool;
}

inline void Stack::setPool(NodePool* pool) {
  Lock lock(_mutex);
  _pool = pool;
}

}

#endif
