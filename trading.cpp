#include <iostream> 
#include <string> 
#include <vector> 
#include <unordered_map>

using namespace std; 

template<typename X> class Stock {
private:

    string symbol; 
    X currentPrice; 
    unordered_map <string, X> Stocks; 

public:
    void setSymbol(string sym);
    void setPrice(X price); 
    string getSymbol(); 
    X getPrice(); 
    void insertNew(string symbol, X price); 
    void printData(); 
    string symbolString(string sym); 

}; 

template<typename X> void Stock<X> :: setSymbol(string sym) { symbol = sym; return; }
template<typename X> void Stock<X> :: setPrice(X price) { currentPrice = price; return; }
template<typename X> string Stock<X> :: getSymbol() { return symbol; }
template<typename X> X Stock<X> :: getPrice() { return currentPrice; }

template<typename X> void Stock<X> :: insertNew(string sym, X price) { 
    setSymbol(sym);  
    setPrice(price);
    Stocks.insert({symbol, currentPrice}); 
    return; 
    }

template<typename X> void Stock<X> :: printData() {
    cout << "-----------------CURRENT STOCK LIST-----------------\n"; 
    for (auto i : Stocks) 
        cout << i.first << " : " << i.second << endl; 
    cout << "----------------------------------------------------\n";
    return;
    }


template<typename X> class Purchase : public Stock<X> {
public:

    string time; 
    X purchasePrice; 

 

    void purchaseStock(X price); 
    X target(X price); 
    void sellStock(); 

};

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
int main () {

string sym = "BRK-B"; 
float price = 355.56; 

Purchase<float> BRKB;
BRKB.insertNew(sym, price); 
BRKB.printData(); 

BRKB.purchaseStock(price);

BRKB.sellStock(); 

price = 400.43; 
BRKB.setPrice(price); 

BRKB.sellStock(); 



    return 0; 
}