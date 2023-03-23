export module Mod2:Order;   // internal partition declaration
import std;

struct Order {
  int count;
  std::string name;
  double price;

  Order(int c, std::string n, double p)
   : count{c}, name{n}, price{p} {
  }
};

