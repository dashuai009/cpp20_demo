export module Mod2:Customer;         // implementation unit of module Mod2
import :Order;       // import internal partition Order 

export class Customer {
private:
    std::string name;
    std::vector<Order> orders;
public:
    Customer(const std::string& n)
            : name{n} {
    }
    void buy(const std::string& ordername, double price) {
        orders.push_back(Order{1, ordername, price});
    }
    void buy(int num, const std::string& ordername, double price) {
        orders.push_back(Order{num, ordername, price});
    }
    double sumPrice() const;
    double averagePrice() const;
    void print() const;
};


double Customer::sumPrice() const
{
  double sum = 0.0;
  for (const Order& od : orders) {  // ERROR with VC++
  //for (const auto& od : orders) {  // OK
    sum += od.count * od.price;
  }
  return sum;
}

double Customer::averagePrice() const
{
  if (orders.empty()) {
    return 0.0;
  }
  return sumPrice() / orders.size();
}


void Customer::print() const
{
    // print name:
    std::cout << name << ":\n";
    // print order entries:
    for (const auto& od : orders) {
        std::cout << std::format("{:3} {:14} {:6.2f} {:6.2f}\n",
                                 od.count, od.name, od.price, od.count * od.price);
    }
    // print sum:
    std::cout << std::format("{:25} ------\n", ' ');
    std::cout << std::format("{:25} {:6.2f}\n", "    Sum:", sumPrice());
}
