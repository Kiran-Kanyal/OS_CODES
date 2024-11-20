#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#define MaxItems 5   // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer
int buffer[BufferSize];
int in = 0;
int out = 0;
int itemCount = 0; // Counter to keep track of items in the buffer
bool bufferFull = false;
bool bufferEmpty = true;
int mutex = 1; // Simulated mutex (1 means unlocked, 0 means locked)
// Function to lock the simulated mutex
void lockMutex()
{
    while (mutex == 0)
        ;      // Busy-wait until the mutex becomes available
    mutex = 0; // Lock the mutex
}
// Function to unlock the simulated mutex
void unlockMutex()
{
    mutex = 1; // Unlock the mutex
}
// Function to wait until the buffer has space
void waitUntilNotFull()
{
    while (bufferFull)
        ; // Busy-wait until the buffer is not full
}
// Function to wait until the buffer is not empty
void waitUntilNotEmpty()
{
    while (bufferEmpty)
        ; // Busy-wait until the buffer is not empty
}
// Function to simulate producing an item
int produceItem()
{
    return rand(); // Produces a random item
}

// Function to insert an item into the buffer
void insertItem(int item)
{
    buffer[in] = item;
    in = (in + 1) % BufferSize;
    itemCount++;
    if (itemCount == BufferSize)
    {
        bufferFull = true;
    }
    bufferEmpty = false;
}
// Function to remove an item from the buffer
int removeItem()
{
    int item = buffer[out];
    out = (out + 1) % BufferSize;
    itemCount--;
    if (itemCount == 0)
    {
        bufferEmpty = true;
    }
    bufferFull = false;
    return item;
}
// Producer function
void producer(int id)
{
    for (int i = 0; i < MaxItems; i++)
    {
        int item = produceItem();
        waitUntilNotFull(); // Wait until there is space in the buffer
        lockMutex();        // Lock the mutex
        insertItem(item);   // Insert the item into the buffer
        printf("Producer %d: Insert Item %d at %d\n", id, item, in - 1);
        unlockMutex();  // Unlock the mutex
        usleep(100000); // Simulate some delay
    }
}
// Consumer function
void consumer(int id)
{
    for (int i = 0; i < MaxItems; i++)
    {
        waitUntilNotEmpty();     // Wait until there are items in the buffer
        lockMutex();             // Lock the mutex
        int item = removeItem(); // Remove the item from the buffer
        printf("Consumer %d: Remove Item %d from %d\n", id, item, out - 1);
        unlockMutex();  // Unlock the mutex
        usleep(150000); // Simulate some delay
    }
}
int main()
{
    // Simulating multiple producers and consumers
    int producerIds[5] = {1, 2, 3, 4, 5};
    int consumerIds[5] = {1, 2, 3, 4, 5};
    // Run all producers
    for (int i = 0; i < 5; i++)
    {
        producer(producerIds[i]);
    }
    // Run all consumers
    for (int i = 0; i < 5; i++)
    {
        consumer(consumerIds[i]);
    }
    return 0;
}
