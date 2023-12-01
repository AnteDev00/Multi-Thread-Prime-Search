#include "Numbers.h"

#include <iostream>
#include <vector>

#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

#include <iomanip>
#include <chrono>

#include <thread>  // self explanatory
#include <mutex>

using namespace std;


void printCurrentTime() {
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::cout << "Current time is " << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S.") << std::setfill('0') << std::setw(3) << ms.count() << std::endl;

}

void Numbers::ArePrime()
{
	int num_threads = thread::hardware_concurrency() - 6; // how many threads
	if (size < num_threads) num_threads = size; 
	// for even workload - we split into equal parts
	int chunk_size = size / num_threads;
	if (chunk_size < 1) chunk_size++;

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
				cout << t << " thread started.\n";
				printCurrentTime();
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
				cout << "\n";
				cout << t << " thread ended (Time:" << duration.count() << ") miliseconds\n";
				mtx.unlock();
			}
		);
	}
	
	// syncing all threads
	for (thread& T : threads) {
		T.join();
	}


	// deciding if Prime & Calculating Compositeness
	for (int i = 0; i < size; i++)
	{
		Number& num = numVector[i];
		num.compositeness = static_cast<double>(num.unique_factors) / num.value;
		if (num.unique_factors > 2)
			num.primeness = "Not-prime";
		else num.primeness = "Prime    ";

	}
	
}


// dont use because printing in paralel is not smart
void Numbers::PrintNumbers()
{
	cout << "\nSlepp 5000 miliseconds for testing purposes";
	this_thread::sleep_for(chrono::milliseconds(5000));

	int num_threads = 3;
	vector<thread> vThreads(num_threads); // 3 threads use
	mutex mtx;
	for (int t = 0; t < num_threads; t++)
	{
		vThreads[t] = thread
		(
			[t, this, &mtx]
			{
				for (int i = t; i < size; i += 3)
				{
					Number& num = numVector[i];				
					cout << "\n[Thread" << t << "]" << " Number " << num.value << "  is    " << num.primeness
						 << "    It has    " << num.unique_factors << "    unique factors. Its' compositeness is "
						 << num.compositeness << " %\n";
				}
			}
		);
	}

	for (thread& T: vThreads)
	{
		T.join();
	}
}

void Numbers::PrintNumbers(int everyX)
{
	cout << "\nSlepp 5000 miliseconds for testing purposes";
	this_thread::sleep_for(chrono::milliseconds(5000));

	for (int i = 0; i < numVector.size(); i+= everyX)
	{
		Number& num = numVector[i];
		cout << "\nNumber  " << num.value << "  is    " << num.primeness 
			 << "    It has    " << num.unique_factors << "  unique factors. Its' compositeness is    " 
			 << std::fixed << std::setprecision(static_cast<int>(std::log10(i+1)) + 1) << num.compositeness*100 << "%\n";
	}
}


void Numbers::FillVector(bool randBool, int digits)
{
	if (randBool == false) FillVector(digits);
	else {
		std::srand(std::time(nullptr));
		digits = pow(10, digits);

		uint64_t ran_num;
		for (int i = 0; i < size; i++)
		{
			ran_num = (static_cast<uint64_t>(std::rand()) * 7863041) % digits;
			numVector.emplace_back(ran_num);
		}
	}
}
void Numbers::FillVector(int digits)
{
	digits = pow(10, digits);
	for (int i = digits; i < digits+size; i++)
	{
		numVector.emplace_back(((i%(digits+size))+1));
	}
}

