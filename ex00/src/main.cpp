#include "BitcoinExchange.hpp"
#include "qolMacros.hpp"

int main(void)
{
	std::map<std::string, float> ts;
	ts = BitcoinExchange::parsePriceData("data.csv");
}
