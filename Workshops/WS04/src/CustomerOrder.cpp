// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 1/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "CustomerOrder.h"
#include "Utilities.h"
#include <algorithm>
#include <exception>
#include <iomanip>
#include <ios>
#include <ostream>
namespace seneca {

size_t CustomerOrder::m_widthField{0};

CustomerOrder::CustomerOrder()
    : m_name(), m_product(), m_cntItem{0}, m_lstItem{nullptr} {}
CustomerOrder::CustomerOrder(const std::string &str) : CustomerOrder() {
  Utilities u;
  size_t pos = 0;
  bool more = false;

  this->m_name = u.extractToken(str, pos, more);
  this->m_product = u.extractToken(str, pos, more);

  auto expectItemCount =
      std::count(str.begin() + pos, str.end(), u.getDelimiter()) + 1;
  this->m_lstItem = new Item *[expectItemCount];
  m_cntItem = 0;
  while (more) {
    this->m_lstItem[m_cntItem] = new Item(u.extractToken(str, pos, more));
    m_cntItem++;
  }
  this->m_widthField = (this->m_widthField > u.getFieldWidth()) ? this->m_widthField : u.getFieldWidth();
}
CustomerOrder::CustomerOrder(const CustomerOrder &) { throw std::exception(); }
CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept {
  m_cntItem = 0;
  m_lstItem = nullptr;
  m_name = "";
  m_product = "";
  *this = std::move(other);
}

CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept {
  for (size_t i = 0; i < this->m_cntItem; i++) {
    delete m_lstItem[i];
  }
  delete[] m_lstItem;


  m_name = other.m_name;
  m_product = other.m_product;
  m_cntItem = other.m_cntItem;
  m_lstItem = other.m_lstItem;
  other.m_lstItem = nullptr;
  other.m_cntItem = 0;
  return *this;
}

CustomerOrder::~CustomerOrder() {
  for (size_t i = 0; i < this->m_cntItem; i++) {
    delete m_lstItem[i];
  }
  delete[] m_lstItem;
}

bool CustomerOrder::isOrderFilled() const {
  for (size_t i = 0; i < m_cntItem; i++) {
    if (!m_lstItem[i]->m_isFilled) {
      return false;
    }
  }
  return true;
}

bool CustomerOrder::isItemFilled(const std::string &name) const {
  for (size_t i = 0; i < m_cntItem; i++) {
    if (!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == name) {
      return false;
    }
  }
  return true;
}

void CustomerOrder::fillItem(Station &station, std::ostream &os) {
  std::string itemName = station.getItemName();
  Item* itemPtr = nullptr;
  for (size_t i = 0; i < m_cntItem; i++) {
    if (!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == station.getItemName()) {
      itemPtr = m_lstItem[i];
      if (station.getQuantity() == 0) {
        os << "    Unable to fill " << this->m_name << ", " << this->m_product << " [" << itemPtr->m_itemName << "]\n";
        continue;;
      }
      break;
    }
  }
  if (itemPtr != nullptr) {
    if (station.getQuantity() > 0) {
      itemPtr->m_isFilled = true;
      itemPtr->m_serialNumber = station.getNextSerialNumber();
      station.updateQuantity();
      os << "    Filled " << this->m_name << ", " << this->m_product << " [" << itemPtr->m_itemName << "]\n";
    } else {
      
      //os << "    Unable to fill " << this->m_name << ", " << this->m_product << " [" << itemPtr->m_itemName << "]\n";
    }
  }
}

void CustomerOrder::display(std::ostream& os) const {
  os << this->m_name << " - " << this->m_product << "\n";
  for (size_t i = 0; i < m_cntItem; i++) {
    os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ');
    os << std::setw(this->m_widthField) << std::setiosflags(std::ios_base::left) << m_lstItem[i]->m_itemName;
    os << std::resetiosflags(std::ios_base::left);
    os << " - ";
    os << ((m_lstItem[i]->m_isFilled) ? "FILLED" : "TO BE FILLED") << "\n";
  }
}

} // namespace seneca
