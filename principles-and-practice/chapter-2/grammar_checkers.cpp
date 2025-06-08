#include <iostream>
#include <string>

int main()
{	
	std::string previous;
	std::string current;
	/**
	 * std::cin >> current is true aslong as no enter or ctrl + d
	 * each world if a space is one iteration of the while loop
	 */
	while( std::cin >> current)
	{
		if(previous == current)
		{
			std::cout << "repeated word: " << current << "\n";
		}
		previous =current;
		std::cout << previous << "\n";
	}
	return 0;
}
