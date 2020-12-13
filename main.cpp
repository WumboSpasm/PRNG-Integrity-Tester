// This program tests the integrity of the Mersenne Twister PRNG by comparing the expected average of summed random numbers to the real average
// To-do: Get floating-point averages to work as expected, maybe add other PRNGs?
#include <iostream>
#include <random>
#include <ctime>

// Global namespace for initializing the Mersenne Twister PRNG
namespace InitRNG
{
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}

// Return a random number distributed between two numbers
int random(int min, int max)
{
	std::uniform_int_distribution randNum{ min, max };
	
	return randNum(InitRNG::mersenne);
}

// Return the expected sum of the random numbers if it were perfectly uniform
int uniformAvg(int min, int max, int seeds)
{
	int range{ (max - min) + 1 };
	
	// Get the uniform distribution of each possible number within a number of seeds
	int dist{ seeds / range };
	
	int sum{};
	
	// Multiply every possible number by its distribution within the number of seeds and add it together
	for (int mult{ min }; mult <= max; ++mult)
	{
		sum += dist * mult;
	}
	
	return sum;
}

// Return a positive number representing the difference between two numbers (in this case, the real and expected averages)
int difference(int first, int second)
{
	if (first > second)
		return first - second;
	else
		return second - first;
}

int main()
{
	// Infinite loop that allows the user to restart the program after it's finished
	while (true)
	{
		// Get and store important variables from user input
		
		// The lowest random number possible
		int minDist{};
		std::cout << "Minimum distribution: ";
		std::cin >> minDist;
		
		// The highest random number possible
		int maxDist{};
		std::cout << "Maximum distribution: ";
		std::cin >> maxDist;
		
		// How many times the program should sum seeded random numbers together in order to help calculate an average
		int numTries{};
		std::cout << "Tries: ";
		std::cin >> numTries;
		
		// How many random numbers should be seeded and added together within a single try 
		int seedNum{};
		std::cout << "Seeds per try: ";
		std::cin >> seedNum;
		
		std::cout << '\n';
		
		int realSum{};
		
		// Seed random numbers a set amount of times and add them together, then print and repeat more times
		// "Try" is spelled incorrectly on purpose to prevent naming collisions
		for (int trie{ 1 }; trie <= numTries; ++trie)
		{
			int randSum{ 0 };
			
			for (int seed{ 1 }; seed <= seedNum; ++seed)
				randSum += random(minDist, maxDist);
			
			realSum += randSum;
			
			std::cout << randSum << '\n';
		}
		
		int expectedAvg{ uniformAvg(minDist, maxDist, seedNum) };
		int realAvg{ realSum / numTries };
		
		// Print final results and ask user if they want to restart
		std::cout << '\n' 
			<< "Expected average: " << expectedAvg << '\n'
			<< "Real average: " << realAvg << '\n'
			<< "Difference: " << difference(expectedAvg, realAvg) << "\n\n"
			<< "Type 'r' to restart or anything else to quit. ";
			
		char option{};
		std::cin >> option;
		
		// Start again from the beginning of the while loop if 'r' is entered, otherwise break the loop and end the program
		if (option == 'r')
			std::cout << '\n';
		else
			break;
	}
	
	return 0;
}