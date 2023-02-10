#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <stack>
#include <thread>

using namespace std;

// constants
const int N = 10000;
const int range = 10;
const int minSleepDuration = 1;
const int maxSleepDuration = 100;

// global variables
stack<int> buffer;
long sum;

// mutex for thread synchronization
mutex m;

// function to add element to stack
void producer(int id)
{
    lock_guard<mutex> guard(m);
    srand(time(NULL) + id); // use unique seed value for each thread

    for (int i = 0; i < N; i++)
    {
        buffer.push(rand() % range + 1);
        // this_thread::sleep_for(chrono::milliseconds(rand() % (maxSleepDuration - minSleepDuration + 1) + minSleepDuration));
    }
}

// function to remove element from stack
void consumer(int id)
{
    lock_guard<mutex> guard(m);
    srand(time(NULL) + id); // use unique seed value for each thread

    for (int i = 0; i < N; i++)
    {
        if (!buffer.empty())
        {
            sum += buffer.top();
            buffer.pop();
            // this_thread::sleep_for(chrono::milliseconds(rand() % (maxSleepDuration - minSleepDuration + 1) + minSleepDuration));
        }
    }
}

// print the sum of all removed elements from the stack
void printSum()
{
    cout << "Sum of all popped elements: " << sum << endl;
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
    producer2.join();
    consumer1.join();
    consumer2.join();

    printSum();

    return 0;
}
