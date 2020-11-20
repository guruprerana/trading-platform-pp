#include "../../api/api.h"
#include "security.h"

EquitySecurity::EquitySecurity(){};

bool EquitySecurity::operator == (const EquitySecurity &es) {
    return this->getName() == es.getName();
}

void Security::setName(std::string name) {
    this->name = name;
}

std::string Security::getName() const {
    return name;
}

void EquitySecurity::setTicker(std::string ticker) {
    this->ticker = ticker;
}

std::string EquitySecurity::getTicker() const {
    return ticker;
}

EquitySecurity::EquitySecurity(std::string symbol) {
    API api;
    auto something = api.getStockData(symbol, 0, 1000);
}

double EquitySecurity::valuation() {
    return 0;
}