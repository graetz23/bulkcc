/**
 * @file bulkccIterator.h
 * @brief Iterator class for sequential stack traversal
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

#ifndef __bulkccIterator_h__
#define __bulkccIterator_h__

#include "./bulkccNode.h"

namespace BULKCC {

#define _VERSION_BULKCC_Iterator_ 1.0

#define _DEBUG_BULKCC_Iterator_

/**
 * @class Iterator
 * @brief Iterator for sequential stack traversal
 *
 * The Iterator class provides a simple mechanism for traversing
 * the stack nodes. It supports getting data, type checking,
 * and moving to the next node.
 *
 * @see Stack
 * @see Node
 */
class Iterator {
public:

  /**
   * @brief Constructor
   *
   * Creates an iterator starting at the given node.
   *
   * @param head Pointer to the head node of the stack
   */
  Iterator(Node* head = 0);

  /**
   * @brief Destructor
   */
  ~Iterator();

  /**
   * @brief Get data from current node
   *
   * Returns the data stored in the current node cast to type T.
   *
   * @tparam T The type to cast data to
   * @return The data, or 0 if at end
   */
  template<class T>
  T get();

  /**
   * @brief Check if current node is of type T
   *
   * @tparam T The type to check for
   * @return true if current node contains type T
   */
  template<class T>
  bool isType() const;

  /**
   * @brief Check if there is a next node
   *
   * @return true if there is a next node
   */
  bool hasNext() const;

  /**
   * @brief Move to next node
   *
   * Advances the iterator to the next node.
   *
   * @return Pointer to the new current node, or 0 if at end
   */
  Node* next();

  /**
   * @brief Get current node
   *
   * @return Pointer to current node, or 0 if at end
   */
  Node* current() const;

  /**
   * @brief Reset iterator to head
   *
   * Moves the iterator back to the head node.
   */
  void reset();

private:

  Node* _current;
  Node* _head;

};

inline Iterator::Iterator(Node* head)
    : _current(head), _head(head) {
#ifdef _DEBUG_BULKCC_Iterator_
  std::cout << "Iterator::Iterator()" << std::endl << std::flush;
#endif
}

inline Iterator::~Iterator() {
#ifdef _DEBUG_BULKCC_Iterator_
  std::cout << "Iterator::~Iterator()" << std::endl << std::flush;
#endif
}

template<class T>
T Iterator::get() {
  if (_current == 0) {
    return 0;
  }
  return _current->getData<T>();
}

template<class T>
bool Iterator::isType() const {
  if (_current == 0) {
    return false;
  }
  return _current->isType<T>();
}

inline bool Iterator::hasNext() const {
  return _current != 0 && _current->getNext() != 0;
}

inline Node* Iterator::next() {
  if (_current != 0) {
    _current = _current->getNext();
  }
  return _current;
}

inline Node* Iterator::current() const {
  return _current;
}

inline void Iterator::reset() {
  _current = _head;
}

}

#endif
