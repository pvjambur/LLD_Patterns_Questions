#include <bits/stdc++.h>
#include <string>

using namespace std;

class Product{
public:
    double price;
    string name;

    Product(double p, string n){
        this->price = p;
        this->name = n;
    }
};

class ShoppingCart{
private:
    vector<Product*> products;

public:
    void addProduct(Product *p){
        products.push_back(p);
    }

    const vector<Product*> getProducts(){
        return products;
    }

    double calculateTotal(){
        double total = 0.0;
        for (auto &p: products){
            total += p->price;
        }
        return total;
    }

    

    
};

class shoppingCartInvoice{
private:
    ShoppingCart* sc;

public:
    shoppingCartInvoice(ShoppingCart* sc1){
        this->sc = sc1;
    }

    void printInvoice(){
        for (auto &p: sc->getProducts()){
            cout << p->name << endl; 
        }
    }
};

class saveToDB{
private:
    ShoppingCart* sc;

public:
    saveToDB(ShoppingCart* cart){
        this->sc = cart;
    }

    void saveToDB1(){
        for (auto &p: sc->getProducts()){
            cout << "Saved: " << p->name << " to DB" << endl;
        }
    }
};

int main(){
    ShoppingCart* sc = new ShoppingCart();

    sc->addProduct(new Product(99.9,"Laptop"));

    return 0;
}