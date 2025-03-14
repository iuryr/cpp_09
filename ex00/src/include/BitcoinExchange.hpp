#ifndef _BITCOIN_EXCHANGE_
#define _BITCOIN_EXCHANGE_

#include <map>
#include <sstream>

class BitcoinExchange
{
private:
	BitcoinExchange(void);
	~BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange& obj);
	BitcoinExchange& operator=(const BitcoinExchange& obj);

public:

	static std::map<std::string, float> priceData;

	static std::map<std::string, float> parsePriceData(std::string filename);
	static std::ostringstream& processInputFile(std::ostringstream& output, std::fstream& file);
	static std::ostringstream& processFirstLine(std::ostringstream& output, std::fstream& file);
	static std::ostringstream& processRemainder(std::ostringstream& output, std::fstream& file);
	static std::ostringstream& processDataLine(std::ostringstream& output, std::fstream& file);
	static int parseDate(std::string date);
	static int parseQty(std::string qty);
};

#endif //_BITCOIN_EXCHANGE_
