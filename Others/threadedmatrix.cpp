#include <iostream>
#include <thread>
using namespace std;

int m1[5][5] = {{1, 2, 3, 4, 5},

                {6, 7, 8, 9, 10},

                {11, 12, 13, 14, 15},

                {16, 17, 18, 19, 20},

                {21, 22, 23, 24, 25}};

int m2[5][3] = {{26, 27, 28},

                {29, 30, 31},

                {32, 33, 34},

                {35, 36, 37},

                {38, 39, 40}};

int result[5][3] = {{0}};

//Function for multiplying two matrices
void multiply(int i, int j)
{
 for (int k = 0; k < 5; k++)
	{
	    result[i][j] += m1[i][k] * m2[k][j];
	}
}

int main()
{
thread t1[5][3];

    for (int i = 0; i < 5; i++) 
	{
        for (int j = 0; j < 3; j++) 
		{
            t1[i][j] = thread(multiply, i, j);
            t1[i][j].join();
        }
    }
    
    for (int i = 0; i < 5; ++i) 
	{
        for (int j = 0; j < 3; ++j) 
		{
            cout << result[i][j] << " ";
			if (j == 2) 
			{
		        cout << "\n";
		    }	
        }
    }

    return 0;
}
