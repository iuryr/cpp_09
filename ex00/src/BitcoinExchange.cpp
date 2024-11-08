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
	else if (file.eof() == false) 
	{
		std::string dateValue = line.substr(0, line.find("|"));
		if (parseDate(dateValue) == 1)
		{
			output << "Error: bad date => " << dateValue << std::endl;
			return output;
		}

		std::string qtyValue = line.substr(line.find("|") + 2, std::string::npos);
		if (parseQty(qtyValue) == 1)
		{
			output << "Error: bad qty input => " << qtyValue << std::endl;
			return output;
		}
		else if (parseQty(qtyValue) == 2)
		{
			output << "Error: too large a number => " << qtyValue << std::endl;
			return output;
		}
		else if (parseQty(qtyValue) == 3)
		{
			output << "Error: not a positive number => " << qtyValue << std::endl;
			return output;
		}

		//do the actual functioning of the program
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

	long long yearNumber = strtoll(year.c_str(), NULL, 10);
	if (yearNumber < 0)
	{
		return 1;
	}

	bool leapYear;
	if ((yearNumber % 4 == 0 && yearNumber % 100 != 0) || (yearNumber % 400 == 0)) {
        leapYear = true;
    }
	else
	{
		leapYear = false;
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

	long long monthNumber = strtoll(month.c_str(), NULL, 10);
	if (monthNumber < 1 || monthNumber > 12)
	{
		return 1;
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

	long long dayNumber = strtoll(day.c_str(), NULL, 10);
	if (dayNumber < 1 || dayNumber > 31)
	{
		return 1;
	}
	if (monthNumber == 4 || monthNumber == 6 ||
		monthNumber == 9 || monthNumber == 11)
	{
		if (dayNumber > 30)
		{
			return 1;
		}
	}
	if (monthNumber == 2)
	{
		if (dayNumber > 29)
		{
			return 1;
		}

		if (leapYear == true && dayNumber > 28)
		{
			return 1;
		}
	}

	return 0;
}

int BitcoinExchange::parseQty(std::string qty)
{
	long double qtyNumber = strtold(qty.c_str(), NULL);
	int plus = 0;
	int minus = 0;
	int dot = 0;

	for (std::string::iterator it = qty.begin(); it != qty.end(); ++it)
	{
		if (*it == '+')
		{
			plus++;
			if (plus > 1 || (plus + minus == 2))
			{
				return 1;
			}
		}
		else if (*it == '-')
		{
			minus++;
			if (minus > 1 || (plus + minus == 2))
			{
				return 1;
			}
		}
		else if (*it == '.')
		{
			dot++;
			if (dot > 1)
			{
				return 1;
			}
		}
		else if (isdigit(*it) == 0)
		{
			return 1;
		}
	}

	if (qtyNumber > 1000)
	{
		return 2;
	}
	if (qtyNumber < 0)
	{
		return 3;
	}

	return 0;
}
