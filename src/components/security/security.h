#ifndef SECURITY_H
#define SECURITY_H

#include "../../api/api.h"

#include <string>

class Security {
public:
    void setName (std::string name);
    std::string getName () const;

protected:
    std::string name;
};

class EquitySecurity: public Security {
public:
    EquitySecurity ();
    EquitySecurity (std::string symbol);

    bool operator == (const EquitySecurity &es);
    double valuation();
    void setTicker (std::string ticker);
    std::string getTicker () const;

private:
    std::string ticker;
};

class DebtSecurity: public Security {
    
};

class DerivativeSecurity: public Security {
    
};

class FuturesDerivativeSecurity: public DerivativeSecurity {
    
};

class ForwardDerivativeSecurity: public DerivativeSecurity {
    
};

class OptionsDerivativeSecurity: public DerivativeSecurity {
    
};

class SwapDerivativeSecurity: public DerivativeSecurity {
    
};

#endif // SECURITY_H