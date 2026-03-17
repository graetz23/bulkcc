/**
 * @file bulkccNode.h
 * @brief Node class for stack elements with type erasure and thread safety
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

#ifndef __bulkccNode_h__
#define __bulkccNode_h__

#include "./bulkccIncl.h"
#include "./bulkccException.h"

namespace BULKCC {

#define _VERSION_BULKCC_Node_ 1.0

#define _NODE_POOL_SIZE_ 10000

#define _DEBUG_BULKCC_Node_

/**
 * @class Node
 * @brief Stack node with type erasure for heterogeneous storage
 *
 * The Node class provides a single element in the stack with support
 * for storing any type through type erasure. Each node contains:
 * - A pointer to the next node (_next)
 * - A data pointer (_data)
 * - Type information for runtime type checking (_typeInfo)
 * - Flags for data presence and usage status
 *
 * @see Stack
 * @see NodePool
 */
class Node {
public:

  /**
   * @struct TypeInfo
   * @brief Type information wrapper for type erasure
   *
   * This structure stores type information for runtime type checking
   * using typeid.
   */
  struct TypeInfo {
    const std::type_info* _info;
    unsigned long _hash;

    /**
     * @brief Default constructor
     */
    TypeInfo() : _info(0), _hash(0) {}

    /**
     * @brief Constructor with type_info
     *
     * @param info Reference to std::type_info
     */
    TypeInfo(const std::type_info& info) : _info(&info) {
      _hash = reinterpret_cast<unsigned long>(&info);
    }

    /**
     * @brief Equality operator
     *
     * @param other TypeInfo to compare
     * @return true if types match
     */
    bool operator==(const TypeInfo& other) const {
      if (_info == other._info) return true;
      if (_info == 0 || other._info == 0) return false;
      return *_info == *other._info;
    }

    /**
     * @brief Inequality operator
     *
     * @param other TypeInfo to compare
     * @return true if types differ
     */
    bool operator!=(const TypeInfo& other) const {
      return !(*this == other);
    }
  };

  /**
   * @brief Default constructor
   *
   * Initializes the node with null data and no next node.
   */
  Node();

  /**
   * @brief Destructor
   */
  virtual ~Node();

  /**
   * @brief Set data in this node
   *
   * Stores the given data in this node with type information.
   *
   * @tparam T The type of data to store
   * @param data The data to store
   */
  template<class T>
  void setData(T data);

  /**
   * @brief Get data from this node
   *
   * Returns the stored data cast to the requested type.
   *
   * @tparam T The type to cast data to
   * @return The stored data
   */
  template<class T>
  T getData();

  /**
   * @brief Check if node contains a specific type
   *
   * @tparam T The type to check for
   * @return true if node contains type T
   */
  template<class T>
  bool isType() const;

  /**
   * @brief Check if data is set
   *
   * @return true if data pointer is not null
   */
  bool isDataSet() const;

  /**
   * @brief Set the next node
   *
   * @param next Pointer to the next node
   */
  void setNext(Node* next);

  /**
   * @brief Get the next node
   *
   * @return Pointer to next node, or 0 if none
   */
  Node* getNext() const;

  /**
   * @brief Set used flag
   *
   * @param used Boolean flag indicating if node is in use
   */
  void setUsed(bool used);

  /**
   * @brief Check if node is used
   *
   * @return true if node is marked as used
   */
  bool isUsed() const;

  Node* _next;
  void* _data;
  TypeInfo _typeInfo;
  bool _dataIsSet;
  bool _isUsed;

};

/**
 * @class NodePool
 * @brief Memory pool for efficient Node allocation
 *
 * The NodePool provides a simple object pool for Node objects,
 * reducing allocation overhead by pre-allocating a pool of nodes.
 *
 * @see Stack
 */
class NodePool {
public:

  static const size_t DEFAULT_POOL_SIZE = _NODE_POOL_SIZE_;

  /**
   * @brief Constructor
   *
   * Creates a node pool with the specified size.
   *
   * @param poolSize Number of nodes to pre-allocate
   */
  NodePool(size_t poolSize = DEFAULT_POOL_SIZE);

  /**
   * @brief Destructor
   *
   * Deletes all pooled nodes.
   */
  ~NodePool();

  /**
   * @brief Allocate a node from the pool
   *
   * @return Pointer to an allocated node
   * @throws Exception if pool is exhausted
   */
  Node* allocate();

  /**
   * @brief Return a node to the pool
   *
   * @param node Pointer to the node to deallocate
   */
  void deallocate(Node* node);

  /**
   * @brief Get count of available nodes
   *
   * @return Number of nodes available in the pool
   */
  size_t getAvailableCount() const;

  /**
   * @brief Get count of allocated nodes
   *
   * @return Number of nodes currently allocated
   */
  size_t getAllocatedCount() const;

  /**
   * @brief Reset the pool
   *
   * Returns all nodes to the free list.
   */
  void reset();

  Mutex _mutex;

private:

  Node* _pool;
  Node* _freeList;
  size_t _poolSize;
  size_t _allocatedCount;

};

inline Node::Node()
    : _next(0), _data(0), _typeInfo(), _dataIsSet(false), _isUsed(false) {
#ifdef _DEBUG_BULKCC_Node_
  std::cout << "Node::Node()" << std::endl << std::flush;
#endif
}

inline Node::~Node() {
#ifdef _DEBUG_BULKCC_Node_
  std::cout << "Node::~Node()" << std::endl << std::flush;
#endif
}

inline bool Node::isDataSet() const {
  return _dataIsSet;
}

inline void Node::setNext(Node* next) {
  _next = next;
}

inline Node* Node::getNext() const {
  return _next;
}

inline void Node::setUsed(bool used) {
  _isUsed = used;
}

inline bool Node::isUsed() const {
  return _isUsed;
}

inline NodePool::NodePool(size_t poolSize)
    : _mutex(), _pool(0), _freeList(0), _poolSize(poolSize), _allocatedCount(0) {
#ifdef _DEBUG_BULKCC_Node_
  std::cout << "NodePool::NodePool(" << poolSize << ")" << std::endl << std::flush;
#endif

  _pool = new Node[_poolSize];
  _freeList = _pool;

  for (size_t i = 0; i < _poolSize - 1; i++) {
    _pool[i]._next = &_pool[i + 1];
  }
  _pool[_poolSize - 1]._next = 0;
}

inline NodePool::~NodePool() {
#ifdef _DEBUG_BULKCC_Node_
  std::cout << "NodePool::~NodePool()" << std::endl << std::flush;
#endif
  delete[] _pool;
  _pool = 0;
}

inline Node* NodePool::allocate() {
  Lock lock(_mutex);

  if (_freeList == 0) {
    throw Exception("NodePool::allocate - pool exhausted");
  }

  Node* node = _freeList;
  _freeList = _freeList->_next;
  node->_next = 0;
  node->_dataIsSet = false;
  node->_isUsed = true;
  _allocatedCount++;

  return node;
}

inline void NodePool::deallocate(Node* node) {
  if (node == 0) return;

  Lock lock(_mutex);

  node->_next = _freeList;
  node->_data = 0;
  node->_dataIsSet = false;
  node->_isUsed = false;
  _freeList = node;
  _allocatedCount--;
}

inline size_t NodePool::getAvailableCount() const {
  return _poolSize - _allocatedCount;
}

inline size_t NodePool::getAllocatedCount() const {
  return _allocatedCount;
}

inline void NodePool::reset() {
  Lock lock(_mutex);

  _freeList = _pool;
  for (size_t i = 0; i < _poolSize - 1; i++) {
    _pool[i]._next = &_pool[i + 1];
  }
  _pool[_poolSize - 1]._next = 0;
  _allocatedCount = 0;
}

}

#endif
