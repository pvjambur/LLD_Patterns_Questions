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

    void saveToSQLDB(){
        cout << "Saved to SQL" << endl;
    }

    void saveToMongoDB(){
        cout << "Saved to MongoDB" << endl;
    }

    void saveToFile(){
        cout << "Saved to File" << endl;
    }
    
};

class Persistence{
private:
    ShoppingCart* sc;

public:
    virtual void save(ShoppingCart* cart) = 0;
};

class SQLPersistence: public Persistence{
public:
    void save(ShoppingCart* cart) override{
        cout << "Saving to SQL DB" << endl;
    }
};

class MongoPersistence: public Persistence{
public:
    void save(ShoppingCart* cart) override{
        cout << "Saving to Mongo" << endl;
    }
};

class FilePersistence: public Persistence{
    void save(ShoppingCart* cart) override{
        cout << "Saving to Files" << endl;
    }
};

int main(){
    ShoppingCart* sc = new ShoppingCart();

    sc->addProduct(new Product(99.9,"Laptop"));
    Persistence* db = new SQLPersistence();
    Persistence* mong = new MongoPersistence();
    Persistence* file = new FilePersistence();

    db->save(sc);
    mong->save(sc);
    file->save(sc);

    return 0;
}