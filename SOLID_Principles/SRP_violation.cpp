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

    void printInvoice(){
        for (auto &p: products){
            cout << p->name << endl; 
        }
    }

    void saveToDB(){
        for (auto &p: products){
            cout << "Saved: " << p->name << " to DB" << endl;
        }
    }
};

int main(){
    ShoppingCart* sc = new ShoppingCart();

    sc->addProduct(new Product(99.9,"Laptop"));

    return 0;
}