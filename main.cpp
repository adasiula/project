#include <iostream>

using namespace std;

uint64_t factorial(int n)
{
    uint64_t wynik=1;
    if(n!=0)
    {
    for(int i=1;i<=n;i++)
    {
        wynik=wynik*i;
    }
    }
    if(n==0)
    {
        wynik=1;
    }
    return wynik;
}

int main()
{
    uint64_t result=factorial(15);
    cout<<result<<endl;



    return 0;
}
