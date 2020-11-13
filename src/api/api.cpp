#include "api.h"

// Constructor of the API class
API::API() {
	// Initiate the CURL object here
}

// Deconstructor of the API class
API::~API() {
	// Delete the CURL object here
}

// Gets the stock from the API
std::map<std::string, double> API::getStockData(std::string stockSymbol, long startTimestamp, long endTimestamp) {
	return {};
}
