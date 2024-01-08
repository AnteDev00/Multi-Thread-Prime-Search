#include "Numbers.h"

#include <iomanip>
#include <mutex>

using namespace std;

void Numbers::ArePrime()
{
	int num_threads = thread::hardware_concurrency() - 1; // how many threads
	if (num_threads > 6)
		num_threads = 6;
	if (size < num_threads) 
		num_threads = size; 
	int chunk_size = size / num_threads;
	if (chunk_size == 0) 
		chunk_size = 1;

	vector<thread> threads(num_threads);
	//Creating Threads and Filling them up with (lambda) Functions
	mutex mtx;
	for (int t = 0; t < num_threads; t++)
	{
		// threads[t] = thread(lambda_funct)  //constructor with fnc in it
		threads[t] = thread
		(
			[this, t, num_threads, &mtx]
			{
				auto startTime = chrono::high_resolution_clock::now();
				
				mtx.lock();
				cout << "Thread number " << t << " started its calculations.\n";
				mtx.unlock();
				
				for (int i = t; i < size; i += num_threads)
				{
					Number& num = numVector[i];
					for (int fac = 2; fac < num.value; fac++)
					{
						if (num.value % fac == 0) num.unique_factors++;
					}
				}
				auto endTime = chrono::high_resolution_clock::now();
				auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

				mtx.lock();
				cout << "\nThread number " << t << " ended. Calulation time :" << duration.count() << " ms";
				mtx.unlock();
			}
		);
	}
	
	// syncing all threads
	for (thread& T : threads) {
		T.join();
	}

	// Prime & Percetage calc
	for (int i = 0; i < size; i++)
	{
		Number& num = numVector[i];
		if (num.unique_factors > 2 || num.value == 1)
			num.primeness = "Not-prime";
		else num.primeness = "Prime    ";
		num.compositeness = static_cast<double>(num.unique_factors) / num.value;
	}
	
}

void Numbers::PrintNumbers(int msDelay)
{
	for (int i = 0; i < numVector.size(); i++)
	{
		this_thread::sleep_for(chrono::milliseconds(msDelay));
		Number& num = numVector[i];
		cout << "\nNumber  " << num.value << "  is    " << num.primeness 
			 << "    It has    " << num.unique_factors << "  unique factors.     Its' compositeness is    " 
			 << std::fixed << std::setprecision(static_cast<int>(std::log10(i+1)) + 1) << num.compositeness*100 << "%\n";
	}
}

