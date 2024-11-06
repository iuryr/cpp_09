#include "BitcoinExchange.hpp"
#include "qolMacros.hpp"

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
	processRemainder(output, file);
	
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
		processDataLine(output, file);
		return output;
	}
}

std::ostringstream& BitcoinExchange::processRemainder(std::ostringstream& output, std::fstream& file)
{
	while (file.eof() == false)
	{
		processDataLine(output, file);
	}

	return output;
}

std::ostringstream& BitcoinExchange::processDataLine(std::ostringstream &output, std::fstream &file)
{
	std::string line;

	std::getline(file, line);
	if (line.find("|") == std::string::npos && file.eof() == false)
	{
		output << "Error: bad input => " << line << std::endl;
		return output;
	}
	else 
	{
		std::string dateValue = line.substr(0, line.find("|"));
		if (parseDate(dateValue) == 1)
		{
			output << "Error: bad date => " << dateValue << std::endl;
			return output;
		};
		std::string qtyValue = line.substr(line.find("|") + 1, std::string::npos);
		println(dateValue);
		println(qtyValue);
	}

	return output;
}


int BitcoinExchange::parseDate(std::string date)
{
	std::string year = date.substr(0, date.find("-"));
	if (year.size() != 4)
	{
		return 1;
	}
	for (std::string::iterator it = year.begin(); it != year.end(); it++)
	{
		if (isdigit(*it) == 0)
		{
			return 1;
		}
	}

	std::string month = date.substr(date.find("-") + 1, 3);
	if (month[month.size() - 1] != '-')
	{
		return 1;
	}
	for (int i = 0; i < 2; i++)
	{
		if (isdigit(month[i]) == 0)
		{
			return 1;
		}
	}

	std::string day = date.substr(date.rfind("-") + 1, std::string::npos);
	if (day.size() != 3) //accounting for whitespace before |
	{
		return 1;
	}
	for (int i = 0; i < 2; i++)
	{
		if (isdigit(day[i]) == 0)
		{
			return 1;
		}
	}

	return 0;
}
