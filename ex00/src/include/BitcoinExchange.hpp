#ifndef _BITCOIN_EXCHANGE_
#define _BITCOIN_EXCHANGE_

#include <map>
#include <sstream>

class BitcoinExchange
{
public:
	BitcoinExchange(void);
	~BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange& obj);
	BitcoinExchange& operator=(const BitcoinExchange& obj);

	static std::map<std::string, float> parsePriceData(std::string filename);
	static std::ostringstream& processInputFile(std::ostringstream& output, std::fstream& file);
	static std::ostringstream& processFirstLine(std::ostringstream& output, std::fstream& file);
};

#endif //_BITCOIN_EXCHANGE_
