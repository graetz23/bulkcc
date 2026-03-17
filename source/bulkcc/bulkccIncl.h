/**
 * @file bulkccIncl.h
 * @brief Common includes and type definitions for BULKCC
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
 *
 * @defgroup BULKCC_Internal Internal Utilities
 * @brief Internal type definitions and includes
 */

#ifndef __bulkccIncl_h__
#define __bulkccIncl_h__

#include <exception> // std::exception
#include <iostream> // std::cout
#include <typeinfo> // typeid().name()
#include <string> // std::string
#include <pthread.h> // pthread_mutex_t

namespace BULKCC {

#define _VERSION_BULKCC_Incl_ 1.0

#define _DEBUG_BULKCC_

typedef std::string Str;

/**
 * @class Mutex
 * @brief Simple mutex wrapper for thread synchronization
 *
 * This class provides a simple wrapper around pthread_mutex for
 * basic thread synchronization.
 */
class Mutex {
public:
  /**
   * @brief Default constructor
   *
   * Initializes the pthread mutex.
   */
  Mutex() {
    pthread_mutex_init(&_mutex, 0);
  }
  /**
   * @brief Destructor
   *
   * Destroys the pthread mutex.
   */
  ~Mutex() {
    pthread_mutex_destroy(&_mutex);
  }
  /**
   * @brief Lock the mutex
   *
   * Acquires the mutex lock. Blocks if the mutex is already locked.
   */
  void lock() {
    pthread_mutex_lock(&_mutex);
  }
  /**
   * @brief Unlock the mutex
   *
   * Releases the mutex lock.
   */
  void unlock() {
    pthread_mutex_unlock(&_mutex);
  }
  /**
   * @brief Get the mutex handle
   *
   * Returns a pointer to the underlying pthread mutex.
   *
   * @return pthread_mutex_t* Pointer to the mutex
   */
  pthread_mutex_t* get() {
    return &_mutex;
  }
private:
  pthread_mutex_t _mutex;
};

/**
 * @class Lock
 * @brief RAII wrapper for automatic mutex locking
 *
 * This class provides a simple RAII wrapper for mutex locking.
 * The mutex is automatically locked on construction and unlocked
 * on destruction.
 */
class Lock {
public:
  /**
   * @brief Constructor with mutex reference
   *
   * Locks the given mutex immediately.
   *
   * @param mutex Reference to the Mutex to lock
   */
  Lock(Mutex& mutex) : _mutex(mutex) {
    _mutex.lock();
  }
  /**
   * @brief Destructor
   *
   * Unlocks the associated mutex.
   */
  ~Lock() {
    _mutex.unlock();
  }
private:
  Mutex& _mutex;
};

} // namespace BULKCC

#endif // __bulkccIncl_h__
