#include "BitcoinExchange.hpp"
#include "qolMacros.hpp"

int main(int argc, char** argv)
{
	if ( argc != 2)
	{
		println("Usage: ./btc input_file");
	}

	std::map<std::string, float> ts;
	ts = BitcoinExchange::parsePriceData("data.csv");
}
