#include "movie.h"
#include "util.h"
#include <cctype>
#include <iostream>



using namespace std;

Movie::Movie(const std::string genre, const std::string rating, const std::string category, const std::string name, double price, int qty) : 
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{ 

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const {
  std::set<std::string> nameKeywords = parseStringToWords(this->getName());
  std::set<std::string> genreKeywords = parseStringToWords(genre_);
  std::set<std::string> keywords = setUnion(nameKeywords, genreKeywords);
  return keywords;
}

std::string Movie::displayString() const {
  std::string result = this->getName();
  result += '\n';
  result += "Genre: " + genre_ + " Rating: " + rating_;
  result += '\n';
  result += std::to_string(this->getPrice()) + " " + std::to_string(this->getQty()) + " left.";

  return result;
}

void Movie::dump(std::ostream& os) const {
    os << "movie" << std::endl;
    os << this->getName() << std::endl;
    os << this->getPrice() << std::endl;
    os << this->getQty() << std::endl;
    os << genre_ << std::endl;
    os << rating_ << std::endl;
}
