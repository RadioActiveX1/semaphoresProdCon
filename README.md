# Producer-Consumer Example with Semaphores

This code example demonstrates the classic producer-consumer problem using C++ threads and semaphores. The producer-consumer problem involves two types of threads: producers that produce items and add them to a shared buffer, and consumers that consume items from the buffer.

In this example, we use semaphores to synchronize the interactions between producers and consumers, ensuring that producers wait when the buffer is full and consumers wait when the buffer is empty. This helps prevent race conditions and ensures proper synchronization between the threads.

## Problem Description

The problem consists of two types of threads:

- Producers: Produce items and add them to the buffer.
- Consumers: Consume items from the buffer.

Both producers and consumers access a shared buffer concurrently. To avoid conflicts and ensure synchronization, we use semaphores to control access to the buffer.

## Code Highlights

- We use the `<thread>`, `<mutex>`, and `<condition_variable>` libraries to manage threads and synchronization primitives.
- The `bufferNotFull` semaphore is used to signal when the buffer is not full, allowing producers to add items.
- The `bufferNotEmpty` semaphore is used to signal when the buffer is not empty, allowing consumers to consume items.
- Mutexes are used to ensure that only one thread at a time can access the shared buffer.
- Producers wait when the buffer is full (`bufferNotFull.wait()`), and consumers wait when the buffer is empty (`bufferNotEmpty.wait()`).

## How to Run

1. Compile the code using a C++ compiler with C++11 support:
   ```sh
   g++ -std=c++11 -o producer_consumer producer_consumer.cpp -lpthread
2. Run the compiled executable:
   ```sh
   ./producer_consumer

## Code Explanation
producer() function: Represents the behavior of producer threads.

consumer() function: Represents the behavior of consumer threads.

mtx mutex: Ensures synchronized access to the shared buffer.

bufferNotFull, bufferNotEmpty semaphores: Used to signal buffer status.

## Additional Notes
This example is simplified to demonstrate the basic concept of producer-consumer synchronization using semaphores. In real-world scenarios, additional considerations and optimizations may be required.

Feel free to experiment with the code and explore more complex synchronization patterns and scenarios.
