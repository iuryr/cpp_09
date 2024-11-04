#include "BitcoinExchange.hpp"

#include <fstream>
#include <cstdlib>
#include <string> //overload of getline methods

std::map<std::string, float> BitcoinExchange::parsePriceData(std::string filename)
{
	std::map<std::string, float> btc_price;
	std::fstream input_file(filename.c_str());

	if (input_file.is_open() == false)
	{
		//return an empy map. user can then check it
		return btc_price;
	}

	std::string line;
	std::getline(input_file, line); //first line -> column names
	std::getline(input_file, line); //capture second line, process inside loop
	while(input_file.eof() == false)
	{
		std::string date, price;
		date = line.substr(0, line.find(",", 0));
		price = line.substr(line.find(",", 0) + 1, std::string::npos);
		btc_price.insert(std::pair<std::string, float>(date, std::atof(price.c_str())));
		// std::cout << date << " | " << btc_price[date] << std::endl;
		std::getline(input_file, line);
	}
	return btc_price;
}

std::ostringstream& BitcoinExchange::processInputFile(std::ostringstream& output, std::fstream& file)
{
	processFirstLine(output, file);
	
	return output;
}

std::ostringstream& BitcoinExchange::processFirstLine(std::ostringstream& output, std::fstream& file)
{
	std::string firstLine;

	std::getline(file, firstLine);
	if (firstLine.compare("date | value") == 0)
	{
		//ignore it
		return output;
	}
	else 
	{
		//TODO
		//check if its a proper line. If so, process it;
		output << "Bad input => " << firstLine << std::endl;
		return output;
	}
}
