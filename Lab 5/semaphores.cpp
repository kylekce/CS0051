// sleep_for function has been disabled/commented out due to a long runtime. (LN 60 & 88)

#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <semaphore>
#include <stack>
#include <thread>

using namespace std;

// constants
const int N = 10000;            // Number of producer repetitions
const int maxStackSize = 10000; // Maximum limit of stack buffer
const int range = 10;
[[maybe_unused]] const int minSleepDuration = 1;
[[maybe_unused]] const int maxSleepDuration = 100;

// global variables
stack<unsigned int> buffer;
unsigned int sum;
int bufferCount;
int producerWaitCount;
int consumerWaitCount;
int producerCount;
int consumerCount;

// mutex and condition variable for thread synchronization
mutex m;
condition_variable cv;

// semaphore for producer and consumer
binary_semaphore producerSem(1), consumerSem(1);

// function to add element to stack
void producer(int id)
{
    producerSem.acquire();
    unique_lock<mutex> lock(m);
    srand(time(nullptr) + id); // use unique seed value for each thread

    for (int i = 0; i < N; i++)
    {
        // wait if stack is full
        if (buffer.size() == maxStackSize)
        {
            producerWaitCount++;
            cout << "Stack Full Producer Waiting " << this_thread::get_id() << endl;
        }
        cv.wait(lock, []()
                { return buffer.size() <= maxStackSize; });

        int n = rand() % range + 1;
        bufferCount += n;
        producerCount++;
        cout << "Thread " << this_thread::get_id() << " Pushed element: " << n << endl;
        buffer.push(n);

        cv.notify_all();
        // this_thread::sleep_for(chrono::milliseconds(rand() % (maxSleepDuration - minSleepDuration + 1) + minSleepDuration));
    }
}

// function to remove element from stack
void consumer(int id)
{
    consumerSem.acquire();
    unique_lock<mutex> lock(m);
    srand(time(nullptr) + id); // use unique seed value for each thread

    for (int i = 0; i < N; i++)
    {
        // wait if stack is empty
        if (buffer.empty())
        {
            consumerWaitCount++;
            cout << "Stack Empty Consumer Waiting " << this_thread::get_id() << endl;
        }
        cv.wait(lock, []()
                { return !buffer.empty(); });

        consumerCount++;
        cout << "Thread " << this_thread::get_id() << " Popped element: " << buffer.top() << endl;
        sum += buffer.top();
        buffer.pop();

        cv.notify_all();
        // this_thread::sleep_for(chrono::milliseconds(rand() % (maxSleepDuration - minSleepDuration + 1) + minSleepDuration));
    }
}

int main()
{
    // create and start threads
    thread producer1(producer, 1);
    thread producer2(producer, 2);
    thread consumer1(consumer, 3);
    thread consumer2(consumer, 4);

    // wait for threads to finish
    producer1.join();
    consumerSem.release();

    consumer1.join();
    producerSem.release();

    producer2.join();
    consumerSem.release();

    consumer2.join();
    producerSem.release();

    // print the stats
    cout << "\nFinal Stats" << endl;
    cout << "Sum of all popped elements: " << sum << endl;
    cout << "Sum of buffer count: " << bufferCount << endl;
    cout << "Count of producer wait: " << producerWaitCount << endl;
    cout << "Count of consumer wait: " << consumerWaitCount << endl;
    cout << "Number of elements produced: " << producerCount << endl;
    cout << "Number of elements consumed: " << consumerCount << endl;

    return 0;
}
