#include "clothing.h"
#include "util.h"
#include <cctype>
#include <iostream>



using namespace std;

Clothing::Clothing(const std::string size, const std::string brand, const std::string category, const std::string name, double price, int qty) : 
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{ 

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> nameKeywords = parseStringToWords(this->getName());
  std::set<std::string> brandKeywords = parseStringToWords(brand_);
  std::set<std::string> keywords = setUnion(nameKeywords, brandKeywords);
  return keywords;
}

std::string Clothing::displayString() const {
  std::string result = this->getName();
  result += '\n';
  result += "Size: " + size_ + " Brand: " + brand_;
  result += '\n';
  result += std::to_string(this->getPrice()) + " " + std::to_string(this->getQty()) + " left.";

  return result;
}

void Clothing::dump(std::ostream& os) const {
    os << "clothing" << std::endl;
    os << this->getName() << std::endl;
    os << this->getPrice() << std::endl;
    os << this->getQty() << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;
}
