#include <iostream>
#include <thread>

using namespace std;

void hellofunction(string str)
{
    for (int i = 0; i <= 1000; i++)
    {
        cout << str + " ";
    }
}

int main()
{
    thread t1(hellofunction, "I");
    t1.join();
}