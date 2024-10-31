#ifndef _BITCOIN_EXCHANGE_
#define _BITCOIN_EXCHANGE_

#include <map>
#include <iostream>

class BitcoinExchange
{
public:
	BitcoinExchange(void);
	~BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange& obj);
	BitcoinExchange& operator=(const BitcoinExchange& obj);

	static std::map<std::string, float> parsePriceData(std::string filename);
};

#endif //_BITCOIN_EXCHANGE_
