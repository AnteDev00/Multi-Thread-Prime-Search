#include <iostream>
#include "Numbers.h"

#include <thread> 

using namespace std;
int main()
{
    cout.flush();
    cout << "Testing first X numbers on primality. (don't go over ~200'000)\n\nEnter the X: ";
    
    int X = 0;
    cin >> X;
    Numbers nums(X);

    cout << "\nTime to calculate!\n\n";
    nums.ArePrime();
  
    cout << "\n\nIn 5 seconds, the numbers are going to be displayed FAST, together with the info.\n";
    this_thread::sleep_for(std::chrono::milliseconds(5000));
    int delayInMs = 0;
    nums.PrintNumbers(delayInMs);

    cout << "\nOver.";
    cout.flush();
}



