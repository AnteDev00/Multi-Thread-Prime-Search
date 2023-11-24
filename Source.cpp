#include <iostream>
#include "Numbers.h"

#include <thread> 

#include <cmath> // delete later
using namespace std;

int main()
{
    // manual input
    /*
	int size = 1;
	cout << "Unesite broj Duljine Polja: ";
	cin >> size;
	Numbers myNums(size);

	int period = 1;
	cout << "Unesite broj Periodicnosti ispisa: ";
	cin >> period;

	int digits = 0;
	cout << "Unesite broj Decimala Brojeva: ";
	cin >> digits;


	myNums.FillVector(false, digits);
	myNums.ArePrime();
	myNums.PrintNumbers(period);
        
    */
    cout.flush();

    // automatic 
    for (int i = 1; i < 1001; i++)
    {
        auto startTime = chrono::high_resolution_clock::now();
        cout << i << "th  sequence started.\n\n";
        Numbers Test(10000);
        Test.FillVector(false, 0);
        Test.ArePrime();
        Test.PrintNumbers(1);
        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "\n" << i << "th  sequence done" << ". Time: "<<duration.count() << " miliseconds \n\n\n" ;
        Test.~Numbers();
        // SLEEP / PAUSE
        this_thread::sleep_for(chrono::milliseconds(100));
        // Namespace::Function(Namespace::Function(Parametar))
              
    }
  
}

