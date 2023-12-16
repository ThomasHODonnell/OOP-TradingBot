#include <iostream> 
#include <string> 
#include <vector> 
#include <unordered_map>

using namespace std; 

template<typename X> class Stock {
private: 

    string symbol; 
    X price; 
    unordered_map <string, X> Stocks; 

public: 

    void insertNew(string symbol, X price); 
    void printData(); 

}; 

template<typename X> void Stock<X> :: insertNew(string sym, X P) { 
    symbol = sym; 
    price = P; 
    Stocks.insert({symbol, price}); 
    return; 
    }

template<typename X> void Stock<X> :: printData() {
    for (auto i : Stocks) 
        cout << i.first << " : " << i.second << endl; 
    return;
    }


int main () {

string sym = "BRK-B"; 
float price = 355.56; 

Stock<float> BRKB;
BRKB.insertNew(sym, price); 
BRKB.printData(); 

    return 0; 
}