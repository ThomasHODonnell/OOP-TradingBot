#include <iostream> 
#include <iomanip>
#include <string> 
#include <vector> 
#include <unordered_map>

using namespace std; 

template<typename X> class Stock {
private:
    string time = "--:--:--"; 
    string symbol; 
    X currentPrice; 
    unordered_map <string, X> stockList; 

public:
    void setTime(); 
    void setSymbol(string sym);
    void setPrice(X price); 
    string getTime(); 
    string getSymbol(); 
    X getPrice(); 
    void insertNew(string symbol, X price); 
    void printData(); 
}; 
template<typename X> class Purchase : public Stock<X> {
private:
    X purchasePrice; 

public:
    void purchaseStock(X price); 
    X target(X price); 
    void sellStock(); 

};
template <typename Y> class Strategy : public Purchase<Y> {
private: 
    bool uptrend; 
    int strength; 
    vector<Y> rollingPrice; 
    vector<Y> highs;
    vector<Y> lows;  

public: 
    void setStrength(int s); 
    void setTrend(bool trend); 
    void setTime(); 
    void setCurrent(Y current); 
    void setRolling(Y current); 
    int getStrength();
    bool getTrend(); 
    bool higherHighs(); 
    void highOrLow(); 
    void priceHistory(); 
    void initializeRolling(Y first, Y second); 
};

template<typename X> void Stock<X> :: setTime() { time = "--:--:--"; return; }
template<typename X> void Stock<X> :: setSymbol(string sym) { symbol = sym; return; }
template<typename X> void Stock<X> :: setPrice(X price) { currentPrice = price; return; }
template<typename X> string Stock<X> :: getTime() { return time; }
template<typename X> string Stock<X> :: getSymbol() { return symbol; }
template<typename X> X Stock<X> :: getPrice() { return currentPrice; }
template<typename X> void Stock<X> :: insertNew(string sym, X price) { 
    setSymbol(sym);  
    setPrice(price);
    stockList.insert({symbol, currentPrice}); 
    return; 
    }
template<typename X> void Stock<X> :: printData() {
    cout << "-----------------CURRENT STOCK LIST-----------------\n"; 
    for (auto i : stockList) 
        cout << i.first << " : " << i.second << endl; 
    cout << "----------------------------------------------------\n";
    return;
    }

template<typename X> void Purchase<X> :: purchaseStock(X price) {
    // TIME API
    this->setPrice(price); 
    purchasePrice = this->getPrice(); 
    cout << "-----------------------BOUGHT-----------------------\n";
    cout << this->getSymbol() << " :: $" << this->getPrice() << endl; 
    cout << "----------------------------------------------------\n";
    return;
    }
template<typename X> X Purchase<X> :: target(X price) {
    // assume 3% return for now
    // need to determine what fees will look like
    float targetGain = 1.03; 
    return price * targetGain;
    }
template<typename X> void Purchase<X> :: sellStock() {
    if (this->getPrice() >= target(purchasePrice)) {
        // API -> sell 
    cout << "-----------------------SOLD-------------------------\n";
    cout << this->getSymbol() << " : $" << this->getPrice() << endl; 
    cout << "----------------------------------------------------\n";
    }
    else {
    cout << "----------------SELL ATTEMPT FAILED-----------------\n";
    cout << this->getSymbol() << " :: "; 
    cout << "$" << this->getPrice() << " < " << target(purchasePrice) << endl; 
    cout << "----------------------------------------------------\n";
    }
    return; 
}

template<typename Y> void Strategy<Y> :: setStrength(int s) { strength = s; return; }
template<typename Y> void Strategy<Y> :: setTrend(bool trend) {uptrend = trend;}
template<typename Y> void Strategy<Y> :: setRolling(Y current) { 
    this->setPrice(current); 
    rollingPrice.push_back(this->getPrice()); 
    highOrLow(); 
    return;
    }
template<typename Y> int  Strategy<Y> :: getStrength() { return strength; }
template<typename Y> bool Strategy<Y> :: getTrend() { return higherHighs(); }
template<typename Y> bool Strategy<Y> :: higherHighs() {
    // let uptrend be 2 cycles
    bool uptrend = false; 
    int a = 0, b = a, c = a, d = a; 
    if (highs[highs.size() - 1] == 0) {a = 2; b = 1; c = 4; d = 3;}
    if (lows[lows.size() - 1] == 0) {a = 1; b = 2; c = 3; d = 4;}
        if (highs[highs.size() - a] > highs[highs.size() - c]) {
                 if (lows[lows.size() - b] > lows[lows.size() - d]) 
                        setStrength(this->getStrength() + 1);
        }
        else {setStrength(this->getStrength() - 1);}
        if (this->getStrength() > 1) uptrend = true;
        if (this->getStrength() > 3) setStrength(3); 
        else if (this->getStrength() < 0) setStrength(0); 
        setTrend(uptrend);

    return uptrend; 
}
template<typename Y> void Strategy<Y> :: highOrLow() {
    if (this->getPrice() < rollingPrice.at(rollingPrice.size() - 2)) {
        if (rollingPrice.at(rollingPrice.size() - 2) > rollingPrice.at(rollingPrice.size() - 3)) {
            highs.push_back(rollingPrice.at(rollingPrice.size() - 2)); 
            lows.push_back((Y) 0.00);
        }
    }
    else if (this->getPrice() > rollingPrice.at(rollingPrice.size() - 2)) {
        if (rollingPrice.at(rollingPrice.size() - 2) < rollingPrice.at(rollingPrice.size() - 3)) {
            lows.push_back(rollingPrice.at(rollingPrice.size() - 2));
            highs.push_back((Y) 0.00);
        }
    }
    else {highs.push_back((Y) 0.00); lows.push_back((Y) 0.00);}
    priceHistory(); 
    return;
}
template<typename Y> void Strategy<Y> :: priceHistory() {
    cout << "------TIME---------ROLLING---------HIGHS---------LOWS------TREND------\n";
    for (int i = 0; i < rollingPrice.size(); i++) {
        cout << "    " << this->getTime(); 
        cout << "      " << setprecision(2) << fixed << rollingPrice[i]; 
        cout << "\t     " << setprecision(2) << fixed << highs[i]; 
        cout << "\t       " << setprecision(2) << fixed << lows[i];  
        cout  << "\t " << this->getTrend() << endl;  
    }
    cout << "----------------------------------------------------------------------\n";
    return;
}
template<typename Y> void Strategy<Y> :: initializeRolling (Y first, Y second) {
    rollingPrice.push_back(first);
    rollingPrice.push_back(second);
    highs.push_back((Y)0.00);
    highs.push_back((Y)0.00);
    lows.push_back((Y)0.00);
    lows.push_back((Y)0.00);
    this->setStrength(0); 
    return;
}
int main () {

// create stock data
string sym = "BRK-B"; 
float price = 1000;
float second = 1100; 

Strategy<float> BRKB; 
BRKB.initializeRolling(price, second); 

// price = 100; 
// BRKB.setRolling(price);
// price = 200; 
// BRKB.setRolling(price);
// price = 50; 
// BRKB.setRolling(price);
// price = 400; 
// BRKB.setRolling(price);
// price = 300; 
// BRKB.setRolling(price);
// price = 500; 
// BRKB.setRolling(price);
// price = 350; 
// BRKB.setRolling(price);


price = 1000; 
BRKB.setRolling(price);

price = 1100; 
BRKB.setRolling(price);

price = 800; 
BRKB.setRolling(price);

price = 900; 
BRKB.setRolling(price);

price = 500; 
BRKB.setRolling(price);

price = 600; 
BRKB.setRolling(price);

price = 550; 
BRKB.setRolling(price);

price = 750; 
BRKB.setRolling(price);

price = 700; 
BRKB.setRolling(price);

price = 900; 
BRKB.setRolling(price);

price = 850; 
BRKB.setRolling(price);

price = 1000; 
BRKB.setRolling(price);


    return 0; 
}