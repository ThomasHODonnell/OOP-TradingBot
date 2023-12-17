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
    Y currentPrice; 
    int strength; 
    vector<Y> rollingPrice; 
    vector<Y> highs;
    vector<Y> lows;  

public: 
    void setTime(); 
    void setCurrent(Y current); 
    void setRolling(Y current); 
    void higherHighs(); 
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

template<typename Y> void Strategy<Y> :: setCurrent(Y current) { currentPrice = current; return;}
template<typename Y> void Strategy<Y> :: setRolling(Y current) { 
    setCurrent(current); 
    rollingPrice.push_back(currentPrice); 
    highOrLow(); 
    return;
    }
template<typename Y> void Strategy<Y> :: higherHighs() {}
template<typename Y> void Strategy<Y> :: highOrLow() {
    if (currentPrice < rollingPrice.at(rollingPrice.size() - 2)) {
        if (rollingPrice.at(rollingPrice.size() - 2) > rollingPrice.at(rollingPrice.size() - 3)) {
            highs.push_back(rollingPrice.at(rollingPrice.size() - 2)); 
            lows.push_back((Y) 0.00);
        }
        }
    

    else if (currentPrice > rollingPrice.at(rollingPrice.size() - 2)) {
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
    cout << "------TIME------ROLLING------HIGHS------LOWS--------\n";
    for (int i = 0; i < rollingPrice.size(); i++) {
        cout << "    " << this->getTime(); 
        cout << "    " << setprecision(2) << fixed << rollingPrice[i]; 
        cout << "\t     " << setprecision(2) << fixed << highs[i]; 
        cout << "\t     " << setprecision(2) << fixed << lows[i] << endl;  
    }
    cout << "----------------------------------------------------\n";
    return;
}
template<typename Y> void Strategy<Y> :: initializeRolling (Y first, Y second) {
    rollingPrice.push_back(first);
    rollingPrice.push_back(second);
    highs.push_back((Y)0.00);
    highs.push_back((Y)0.00);
    lows.push_back((Y)0.00);
    lows.push_back((Y)0.00);
    return;
}
int main () {

// create stock data
string sym = "BRK-B"; 
float price = 355.56; 

// create instance, insert to stock list
Strategy<float> BRKB;
BRKB.insertNew(sym, price); 
BRKB.printData(); 

// buy stock
BRKB.purchaseStock(price);

// attempt to sell stock (would not make money) -> failed
BRKB.sellStock(); 

// redefine price -> sell for profit
price = 400.43; 
BRKB.setPrice(price); 
BRKB.sellStock(); 

// test strategy 
//BRKB.setRolling(price); 
float second = 350; 
BRKB.initializeRolling(price, second);

price = 405.00;
BRKB.setRolling(price); 




    return 0; 
}