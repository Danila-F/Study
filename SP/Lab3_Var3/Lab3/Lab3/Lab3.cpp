#include <iostream>
#include <string>
#include <math.h>
using namespace std;

float MathFunc(float X, float N)
{
    float F = 0;
    float SumRes = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (X + j >= 0 && ((2. * i * j) - 1) != 0)
            {
                SumRes += (j + pow(X + j, 1. / 7)) / ((2. * i * j) - 1);
            }
            else
            {
                cout << "Uncorrect input!" << endl;
                break;
            }
        }
        F += 1/SumRes;
        SumRes = 0;
    }
    return F;
}

void main()
{
    float X, N, F;
    cout << "Please, enter two numbers (X, N):" << endl;
    cin >> X >> N;
    F = MathFunc(X, N);
    cout << "The result of executing MathFunc is: " << F << endl;
    system("pause");
    return;
}
