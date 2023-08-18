#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

const int bufferSize = 5;
vector<int> buffer(bufferSize); // Buffer to store produced items
int itemCount = 0; // Number of items in the buffer

mutex mtx; // Mutex for synchronization
condition_variable bufferNotFull, bufferNotEmpty; // Condition variables for signaling

// Producer function
void producer() {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx); // Lock the mutex

        // Wait until the buffer is not full
        bufferNotFull.wait(lock, [] { return itemCount < bufferSize; });

        // Produce an item and add it to the buffer
        buffer[itemCount++] = i;
        cout << "Produced: " << i << endl;

        lock.unlock(); // Unlock the mutex
        bufferNotEmpty.notify_all(); // Notify consumers that the buffer is not empty

        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate processing time
    }
}

// Consumer function
void consumer() {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx); // Lock the mutex

        // Wait until the buffer is not empty
        bufferNotEmpty.wait(lock, [] { return itemCount > 0; });

        // Consume an item from the buffer
        int consumed = buffer[--itemCount];
        cout << "Consumed: " << consumed << endl;

        lock.unlock(); // Unlock the mutex
        bufferNotFull.notify_all(); // Notify producers that the buffer is not full

        this_thread::sleep_for(chrono::milliseconds(200)); // Simulate processing time
    }
}

int main() {
    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join(); // Wait for producer thread to finish
    consumerThread.join(); // Wait for consumer thread to finish

    return 0;
}
