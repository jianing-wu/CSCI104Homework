#include <sstream>
#include "book.h"
#include "util.h"

Book::Book(const std::string category, 
	const std::string name, double price, int qty, 
	const std::string isbn, const std::string author) : 
	Product(category, name, price, qty) {
		isbn_ = isbn;
		author_ = author;		
}

Book::~Book() {
}

std::string Book::getIsbn() const {
	return isbn_;
}
std::string Book::getAuthor() const {
	return author_;
}

/**
* Extract keywords from author, name and isbn
*/
std::set<std::string> Book::keywords() const {
	std::set<std::string> authorKeywords = parseStringToWords(author_);
	std::set<std::string> nameKeywords = parseStringToWords(name_);
	std::set<std::string> keywords = setUnion(authorKeywords, nameKeywords);
	keywords.insert(isbn_);
	return keywords;
}

/**
* Display Book in a single string
*/
std::string Book::displayString() const {
	std::stringstream ss;
	ss << name_ << "\n";
	ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
	ss << price_ << " " << qty_ << " left.";
	return ss.str();
}

/**
* Dump Book to output stream
*/
void Book::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n";
	os << isbn_ << "\n" << author_ << std::endl;
}
