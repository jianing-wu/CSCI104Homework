#include <sstream>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, 
	const std::string size, const std::string brand) :
	Product(category, name, price, qty)
{
	size_ = size;
	brand_ = brand;
}

Clothing::~Clothing() {
}

std::string Clothing::getSize() const {
	return size_;
}

std::string Clothing::getBrand() const {
	return brand_;
}

/**
* Extract keywords from both brand and name
*/
std::set<std::string> Clothing::keywords() const {
	std::set<std::string> brandKeywords = parseStringToWords(brand_);
	std::set<std::string> nameKeywords = parseStringToWords(name_);
	return setUnion(brandKeywords, nameKeywords);
}

/**
* Display Clothing in a single string
*/
std::string Clothing::displayString() const {
	std::stringstream ss;
	ss << name_ << "\n";
	ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
	ss << price_ << " " << qty_ << " left.";
	return ss.str();
}

/**
* Dump Clothing to output stream
*/
void Clothing::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n";
	os << size_ << "\n" << brand_ << std::endl;
}