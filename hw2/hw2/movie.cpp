#include <sstream>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, 
	const std::string genre, const std::string rating) :
	Product(category, name, price, qty)
{
	genre_ = genre;
	rating_ = rating;
}

Movie::~Movie() {
}

	
std::string Movie::getGenre() const {
	return genre_;
}

std::string Movie::getRating() const {
	return rating_;
}

/**
* Extract keywords from both genre and name
*/
std::set<std::string> Movie::keywords() const {
	std::set<std::string> genreKeywords = parseStringToWords(genre_);
	std::set<std::string> nameKeywords = parseStringToWords(name_);
	return setUnion(genreKeywords, nameKeywords);
}

/**
* Display Movie in a single string
*/
std::string Movie::displayString() const {
	std::stringstream ss;
	ss << name_ << "\n";
	ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
	ss << price_ << " " << qty_ << " left.";
	return ss.str();
}

/**
* Dump Movie to output stream
*/
void Movie::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n";
	os << genre_ << "\n" << rating_ << std::endl;
}
