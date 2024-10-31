#include "BitcoinExchange.hpp"

#include <fstream>
#include <cstdlib>

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
		std::cout << date << " | " << btc_price[date] << std::endl;
		std::getline(input_file, line);
	}
	return btc_price;
}
