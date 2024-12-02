// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 1/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include "Station.h"
#include <cstddef>
#include <string>
namespace seneca {
struct Item {
  std::string m_itemName;
  size_t m_serialNumber{0};
  bool m_isFilled{false};

  Item(const std::string &src) : m_itemName(src) {};
};
class CustomerOrder {
  std::string m_name;
  std::string m_product;
  size_t m_cntItem;
  Item** m_lstItem;

  static size_t m_widthField;

  public:
  CustomerOrder();
  CustomerOrder(const std::string&);
  CustomerOrder(const CustomerOrder&);
  CustomerOrder(CustomerOrder&&) noexcept;
  CustomerOrder& operator=(const CustomerOrder&) = delete;
  CustomerOrder& operator=(CustomerOrder&&) noexcept;
  ~CustomerOrder();

  bool isOrderFilled() const;
  bool isItemFilled(const std::string&) const;
  void fillItem(Station&, std::ostream&);
  void display(std::ostream&) const;

};
} // namespace seneca

#endif // SENECA_CUSTOMERORDER_H
