#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>
#include <list>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile);

    bool addToCart(std::string username, Product*);

    std::list<Product*> findCart(std::string username, bool& invalidUser);

    bool buyCart(std::string username);

private:
	std::set<Product*> products_;
	std::set<User*> users_;
	// Keyword maps to a set of products
	std::map<std::string, std::set<Product*>*> searchMap_;
	// Username maps to user
	std::map<std::string, User*> userMap_;
	// User maps to cart (a list of products)
	std::map<User*, std::list<Product*>*> cartMap_;
};

#endif