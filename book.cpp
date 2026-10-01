#include "book.h"
#include "util.h"
#include <cctype>
#include <iostream>



using namespace std;

Book::Book(const std::string isbn, const std::string author, const std::string category, const std::string name, double price, int qty) : 
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author)
{ 

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const {
  std::set<std::string> nameKeywords = parseStringToWords(this->getName());
  std::set<std::string> authorKeywords = parseStringToWords(author_);
  std::set<std::string> keywords = setUnion(nameKeywords, authorKeywords);
  keywords.insert(isbn_);
  return keywords;
}

std::string Book::displayString() const {
  std::string result = this->getName();
  result += '\n';
  result += "Author: " + author_ + " ISBN: " + isbn_;
  result += '\n';
  result += std::to_string(this->getPrice()) + " " + std::to_string(this->getQty()) + " left.";

  return result;
}

void Book::dump(std::ostream& os) const {
    os << "book" << std::endl;
    os << this->getName() << std::endl;
    os << this->getPrice() << std::endl;
    os << this->getQty() << std::endl;
    os << isbn_ << std::endl;
    os << author_ << std::endl;
}
