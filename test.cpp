#include <iostream>
#include <thread>
#include <string>
using namespace std;
void hellofunction(int n, string str){
for(int i=0; i<n; i++)
cout << "Hello from function... " << " " << str << endl;
}
class HelloObject {
public:
void objectfunction(int n, string str);
};
void HelloObject::objectfunction(int n, string str){
for(int i=0; i<n; i++)
cout << "Hello from object function"  << " " << str << endl;
}

int main()
{
cout << "Hello World from main()" << endl;
thread t1(hellofunction,5, "FEUTECH");
HelloObject ho;
thread t2(&HelloObject::objectfunction, &ho, 5, "FEUTECH"); 
t1.join();
t2.join();
cout << "\nmain() program ends..." << endl;
}