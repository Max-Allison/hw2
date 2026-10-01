#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <string>
#include <set>
#include <map>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    bool addToCart(User* u, size_t hitIndex);
    bool findUser(User* u);
    std::vector<Product*> viewCart(User* u);
    void buyCart(User* u);
    User* lookupUser(std::string name);

protected:
    std::set<Product*> products_;
    std::set<User*> users_;
    std::map<std::string, std::set<Product*>> keyMap_;
    std::vector<Product*> prevHits_;
    std::map<User*, std::queue<Product*>> cartMap_;
    std::map<std::string, User*> userMap_;
};

#endif