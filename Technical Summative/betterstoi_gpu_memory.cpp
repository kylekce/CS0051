#include <iostream>
#include <chrono>
#include <cstring>

using namespace std;

int main()
{
    // Input a string of positive integer
    char input[10000];
    cout << "Enter a string of positive integer: ";
    scanf("%s", input);

    int size = strlen(input);
    int result[size];

    // Convert string to int array
    auto start = chrono::high_resolution_clock::now();

    #pragma acc data copyin(input[0:size]) copyout(result[0:size])
    {
        #pragma acc parallel loop present(input[0:size], result[0:size]) vector_length(32)
        for (int i = 0; i < size; i++)
            result[i] = input[i] - '0';
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    // Display result
    cout << "The integer array is: ";
    for (int i = 0; i < 5; i++)
        cout << result[i];
    cout << "...";
    for (int i = size - 5; i < size; i++)
        cout << result[i];
    cout << " (Input: "<< size << " chars" << ", Output: " << size << " ints"
         << ", Runtime is: " << duration.count() << " ms)" << endl;
}



