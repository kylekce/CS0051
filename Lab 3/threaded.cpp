#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <mutex>

using namespace std;

// constants for the program
const long MAX = 500000000;
const int RANGE = 6;

// other declarations
double originalTime = 13563; // original program's time
unsigned long long int sum = 0;
vector<int> num(MAX);

mutex m;

// variables for histogram
int h1 = 0;
int h2 = 0;
int h3 = 0;
int h4 = 0;
int h5 = 0;

void vectorSum();
void histogram();

int main()
{
    // generates random numbers 1 to 5
    for (int i = 0; i < MAX; i++)
    {
        num[i] = rand() % RANGE;
        // cout << num[i] << endl; // prints the random numbers
    }

    // gets the initial time
    auto start = chrono::high_resolution_clock::now();

    // creates and starts the threads
    thread t1 = thread(vectorSum);
    thread t2 = thread(histogram);

    // waits for the threads
    t1.join();
    t2.join();

    // calculates the process time
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    // prints the histogram
    cout << "Histogram Result is : " << endl;
    cout << "1  ----> " << h1 << " SUM : " << h1 << endl;
    cout << "2  ----> " << h1 << " SUM : " << h2 * 2 << endl;
    cout << "3  ----> " << h1 << " SUM : " << h3 * 3 << endl;
    cout << "4  ----> " << h1 << " SUM : " << h4 * 4 << endl;
    cout << "5  ----> " << h1 << " SUM : " << h5 * 5 << endl;

    // prints the results
    unsigned long long int histogramsum = h1 + (h2 * 2) + (h3 * 3) + (h4 * 4) + (h5 * 5);
    cout << "The sum of the vector is : " << sum << " and the sum of the histogram is " << histogramsum << endl;
    cout << "TOTAL RUNNING TIME IS : " << duration.count() << " milliseconds...." << endl;

    // Calculates the percentage of enhancement
    cout << "Enhanced by " << (((originalTime - duration.count()) / originalTime) * 100) << "%" << endl;

    return 0;
}

// increments the sum
void vectorSum()
{
    lock_guard<mutex> guard(m);
    for (int i = 0; i < MAX; i++)
    {
        sum = sum + num[i];
    }
}

// increments the histogram
void histogram()
{
    lock_guard<mutex> guard(m);
    for (int i = 0; i < MAX; i++)
    {
        switch (num[i])
        {
        case 1:
            h1++;
            break;
        case 2:
            h2++;
            break;
        case 3:
            h3++;
            break;
        case 4:
            h4++;
            break;
        case 5:
            h5++;
            break;
        }
    }
}