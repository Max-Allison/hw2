#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <set>


class Clothing : public Product {
public:
  Clothing(const std::string size, const std::string brand, const std::string category, const std::string name, double price, int qty);
  ~Clothing();
  std::set<std::string> keywords() const override;
  std::string displayString() const override;
  void dump(std::ostream& os) const override;
protected:
  std::string size_;
  std::string brand_;
};

#endif