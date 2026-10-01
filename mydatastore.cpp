#include "mydatastore.h"
#include "util.h"
#include <string>
#include <set>
#include <map>

using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
    for (Product* p : products_) {
        delete p;
    }
    
    for (User* u : users_) {
        delete u;
    }
}


void MyDataStore::addProduct(Product* p) {
    if (products_.find(p) == products_.end()) {
        products_.insert(p);
        for (std::set<std::string>::iterator it = p->keywords().begin(); it != p->keywords().end(); ++it) {
            keyMap_[*it].insert(p);
        }
    }
}

void MyDataStore::addUser(User* u) {
    if (users_.find(u) == users_.end()) {
        users_.insert(u);
        cartMap_[u];
        userMap_[convToLower(u->getName())] = u;
    }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    if (terms.size() == 0) {
        std::vector<Product*> hits(products_.begin(), products_.end());
        return hits;
    }

    std::set<Product*> hitset;

    if (keyMap_.count(terms[0])) {
        hitset = keyMap_[terms[0]];
    }
    //AND
    if (type == 0) {
        for(size_t i = 1; i < terms.size(); ++i) {
            if (keyMap_.count(terms[i])) {
                std::set<Product*> currentset = keyMap_[terms[i]];
                hitset = setIntersection(hitset, currentset);
            } else {
                hitset.clear();
                break;
            }
        }
    } // OR
    else {
        for(size_t i = 1; i < terms.size(); ++i) {
            if (keyMap_.count(terms[i])) {
                std::set<Product*> currentset = keyMap_[terms[i]];
                hitset = setUnion(hitset, currentset);
            }
        }
    }

    std::vector<Product*> hits(hitset.begin(), hitset.end());
    prevHits_ = hits;
    return hits;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << "\n";
    for (Product* p : products_) {
        p->dump(ofile); 
    }
    ofile << "<products>" << "\n";

    ofile << "<users>" << "\n";
    for (User* u : users_) {
        u->dump(ofile); 
    }
    ofile << "</users>" << "\n";
}

bool MyDataStore::addToCart(User* u, size_t hitIndex) {
    if (hitIndex > prevHits_.size() || hitIndex <= 0) {
        return false;
    }

    if (u == nullptr || users_.find(u) == users_.end()) {
        return false;
    }

    cartMap_[u].push(prevHits_[hitIndex - 1]);
    return true;
}

std::vector<Product*> MyDataStore::viewCart(User* u) {
    std::vector<Product*> cartVec;
    std::queue<Product*> cartQueue = cartMap_[u];
    while (!cartQueue.empty()) {
        cartVec.push_back(cartQueue.front());
        cartQueue.pop();
    }

    return cartVec;
}

bool MyDataStore::findUser(User* u) {
    if (u == nullptr || users_.find(u) == users_.end()) {
        return false;
    } else {
        return true;
    }
}

void MyDataStore::buyCart(User* u) {
    if (cartMap_.find(u) == cartMap_.end()) {
        return; 
    }
    std::queue<Product*> cart = cartMap_[u];
    std::queue<Product*> remainingCart;
    while (!cart.empty()) {
        if (cart.front()->getQty() > 0 && u->getBalance() >= cart.front()->getPrice()) {
            u->deductAmount(cart.front()->getPrice());
            cart.front()->subtractQty(1);
            cart.pop();
        } else {
            remainingCart.push(cart.front());
            cart.pop();
        }
    }
    
    cartMap_[u] = remainingCart;
}

User* MyDataStore::lookupUser(std::string name) {
    if (userMap_.count(convToLower(name))) {
        return userMap_[convToLower(name)];
    }
    return nullptr;
}