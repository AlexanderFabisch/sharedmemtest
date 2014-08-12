#ifndef __SharedMemory_H__
#define __SharedMemory_H__

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

class SharedMemory
{
  const std::string identifier;
  const size_t maxSize;

  int fileDescriptor;
  void* sharedMemory;
  sem_t* semaphore;

  bool successful;

public:
  SharedMemory(const std::string& identifier, size_t maxSize);
  ~SharedMemory();

  void closeAccess();
  bool success() { return successful; }

  template<class T>
  void initializeMemory(const T& initialValue)
  {
    T* pointer = (T*) sharedMemory;
    *pointer = initialValue;
    sem_post(semaphore);
  }

  template<class T>
  SharedMemory& operator<<(const T& value)
  {
    sem_wait(semaphore);
    T* pointer = (T*) sharedMemory;
    *pointer = value;
    sem_post(semaphore);
    return *this;
  }

  template<class T>
  SharedMemory& operator>>(T& value)
  {
    sem_wait(semaphore);
    value = *((T*) sharedMemory);
    sem_post(semaphore);
    return *this;
  }
};

#endif
