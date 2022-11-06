#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
	std::map<std::string, std::set<Product*>*>::iterator itSearch;
	for (itSearch = searchMap_.begin(); itSearch != searchMap_.end(); ++itSearch) {
		delete itSearch->second;
	}
	std::map<User*, std::list<Product*>*>::iterator itCart;
	for (itCart = cartMap_.begin(); itCart != cartMap_.end(); ++itCart) {
		delete itCart->second;
	}
}

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p) {
	// add product
	products_.insert(p);

	// Add keyword mapping
	std::set<std::string> keywords = p->keywords();
	std::set<std::string>::iterator itKey;

	for (itKey = keywords.begin(); itKey != keywords.end(); ++itKey) {
		std::map<std::string, std::set<Product*>*>::iterator mapIt;
		std::string key = convToLower(*itKey);
		
		mapIt = searchMap_.find(key);
		if (mapIt != searchMap_.end()) {
			mapIt->second->insert(p);
		} else {
			std::set<Product*>* productSet = new std::set<Product*>;
			productSet->insert(p);
			searchMap_[key] = productSet;
		}
	}
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u) {
	if (userMap_.find(u->getName()) != userMap_.end()) {
		return;
	}
	users_.insert(u);
	userMap_[convToLower(u->getName())] = u;
}

/**
* Add product to user's cart (a list of products per user)
*/
bool MyDataStore::addToCart(std::string username, Product* p) {
	// Find user based on Username 
	std::map<std::string, User*>::iterator itUser = userMap_.find(username);
	std::set<Product*>::iterator itProd = products_.find(p);
	if (itUser == userMap_.end() || itProd == products_.end()) {
		return false;
	}
	User* u = itUser->second;

	// Find cart using User pointer
	// and add product to the cart list
	std::map<User*, std::list<Product*>*>::iterator itCart = cartMap_.find(u);
	if (itCart != cartMap_.end()) {
		itCart->second->push_back(p);
	} else {
		std::list<Product*>* cart = new std::list<Product*>;
		cart->push_back(p);
		cartMap_[u] = cart;
	}
	return true;
}


/**
* Find the cart for user (a list of products)
*/
std::list<Product*> MyDataStore::findCart(std::string username, bool& invalidUser) {
	std::list<Product*> cart;

	// Check if user exists and find the user if exists
	std::map<std::string, User*>::iterator itUser = userMap_.find(username);
	if (itUser == userMap_.end()) {
		invalidUser = true;
		return cart;
	}
	User* u = itUser->second;

	// Find the cart from cart map for the user
	std::map<User*, std::list<Product*>*>::iterator itCart = cartMap_.find(u);
	if (itCart != cartMap_.end()) {
		cart = *(itCart->second);
	}
	return cart;
}

/**
* Buy cart of a user
* If user does not exist, return false
* If cart is empty, do nothing
* Buy items in cart one by one.
* For one item, if user has enough balance and 
* item is in stock, reduce the stock quantity, susbtract the price
* from user's balance and remove the item from user's cart. 
* Otherwise, skip this item and process the next one. 
*/
bool MyDataStore::buyCart(std::string username) {
	// Check if user exists
	std::map<std::string, User*>::iterator itUser = userMap_.find(username);
	if (itUser == userMap_.end()) {
		return false;
	}
	User* u = itUser->second;

	// Find user's cart 
	std::map<User*, std::list<Product*>*>::iterator itCart = cartMap_.find(u);
	if (itCart == cartMap_.end()) {
		return true;
	}
	std::list<Product*>* cart = itCart->second;

	// Buy items
	std::list<Product*>::iterator it = cart->begin();
	std::vector<std::list<Product*>::iterator> boughtItems;
	for (it = cart->begin(); it != cart->end(); ++it) {
		Product* p = *it;
		if (p->getQty() > 0 && u->getBalance() > p->getPrice()) {
			p->subtractQty(1);
			u->deductAmount(p->getPrice());
			boughtItems.push_back(it);
		}
	}

	// Delete bought items
	for (unsigned int i = 0; i < boughtItems.size(); i++) {
		cart->erase(boughtItems[i]);
	}
	return true;
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	// std::cout << "start search"<< std::endl;
	std::vector<Product*> results;
	if (type != 0 && type != 1) {
		return results;
	}

	std::set<Product*> products;
	for (unsigned int i = 0; i < terms.size(); i++) {
		std::set<Product*> matches;
		// std::cout << "terms["<< i << "]: "<< terms[i] << std::endl;
		// std::cout << "searchMap_ size: "<< searchMap_.size() << std::endl;
		std::map<std::string, std::set<Product*>*>::iterator mapIt = searchMap_.find(terms[i]);
		if (mapIt != searchMap_.end()){
			matches = *(mapIt->second);
		}
		// std::cout << matches.size() << " matches" << std::endl;
		if (type == 0) { // AND
			if (i == 0) {
				products = matches;
			} else {
				products = setIntersection(products, matches);
			}
		} else if (type == 1){ // OR
			products = setUnion(products, matches);
		}
	}

	std::set<Product*>::iterator it;
	for(it = products.begin(); it != products.end(); ++it) {
		results.push_back(*it);
	}
	return results;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>\n";
	std::set<Product*>::iterator itProd;
	for (itProd = products_.begin(); itProd != products_.end(); ++itProd) {
		(*itProd)->dump(ofile);
	}
	ofile << "</products>\n";
	ofile << "<users>\n";
	std::set<User*>::iterator itUser;
	for (itUser = users_.begin(); itUser != users_.end(); ++itUser) {
		(*itUser)->dump(ofile);
	}
	ofile << "</users>" << std::endl;
}