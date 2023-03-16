#include <iostream>
#include <chrono>

using namespace std;

int main()
{
    int a[300000] = {0};
    int sumpair[150000] = {0};

    int sum1 = 0;
    for (int i = 0; i < 300000; i++)
    {
        a[i] = i;
        sum1 += i;
    }

    auto start = chrono::high_resolution_clock::now();
#pragma acc data copyin(a, sumpair), copyout(sumpair)
    {
#pragma acc parallel
        {
#pragma acc loop independent
            for (int i = 0; i < 150000; i++)
            {
                sumpair[i] = a[i * 2] + a[(i * 2) + 1];
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();

    auto total = chrono::duration_cast<chrono::microseconds>(end - start);

    int sum2 = 0;
    for (int i = 0; i < 150000; i++)
    {
        sum2 += sumpair[i];
    }

    cout << sum1 << "-----------" << sum2 << endl;
    cout << "TOTAL RUNNING TIME : " << total.count() << " microseconds...[PARALLEL]" << endl;

    return 0;
}