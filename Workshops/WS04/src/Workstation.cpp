// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 8/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "Workstation.h"
#include "CustomerOrder.h"
#include <deque>
#include <ostream>
#include <string>
namespace seneca {
  std::deque<CustomerOrder> g_pending{};
  std::deque<CustomerOrder> g_incomplete{};
  std::deque<CustomerOrder> g_completed{};
  Workstation::Workstation(const std::string& str) : Station(str), m_pNextStation(nullptr) {}
  void Workstation::fill(std::ostream& os) {
    if (!m_orders.empty())
    m_orders.front().fillItem(*this, os);
  }
  bool Workstation::attempToMoveOrder() {
    if (this->m_orders.empty()) {
      return false;
    }
    std::string itemName = this->getItemName();
    if (m_orders.front().isItemFilled(itemName) || this->getQuantity() == 0) {
      if (m_pNextStation) {
        *m_pNextStation += std::move(m_orders.front());
      } else {
        if (m_orders.front().isOrderFilled()) {
          g_completed.push_back(std::move(m_orders.front()));
        } else {
          g_incomplete.push_back(std::move(m_orders.front()));
        }
      }
      m_orders.pop_front();
    } else {
      return false;
    }
    return true;
  }
  void Workstation::setNextStation(Workstation* station) {
    m_pNextStation = station;
  }
  Workstation* Workstation::getNextStation() const {
    return m_pNextStation;
  }
  void Workstation::display(std::ostream& os) const {
    os << this->getItemName() << " --> ";
    os << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line");
    os << "\n";
  }
  Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
    this->m_orders.push_back(std::move(newOrder));
    return *this;
  }
}
