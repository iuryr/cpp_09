#include "BitcoinExchange.hpp"
#include "qolMacros.hpp"
#include <fstream>
#include <sstream>

bool isFileEmpty(std::fstream& file)
{
	//move read pointer to the eof
	file.seekg(0, std::ios::end);

	//get position of read pointer
	std::streampos fileSize = file.tellg();

	//move read pointer back to beginning
	file.seekg(0, std::ios::beg);

	if (fileSize == 0)
	{
		return true;
	}
	return false;
}

int main(int argc, char** argv)
{
	if ( argc != 2)
	{
		println("Usage: ./btc input_file");
		return 1;
	}

	std::fstream inputFile(argv[1], std::fstream::in); 
	if (inputFile.is_open() == false)
	{
		println("Could not open input file.");
		return 1;
	}

	if (isFileEmpty(inputFile) == true)
	{
		println("Provided file is empty.");
		return 1;
	}

	BitcoinExchange::priceData = BitcoinExchange::parsePriceData("data.csv");

	std::ostringstream output;
	BitcoinExchange::processInputFile(output, inputFile);

	std::cout << output.str();

	inputFile.close();
}
