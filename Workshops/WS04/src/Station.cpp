// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 1/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "Station.h"
#include "Utilities.h"
#include <iomanip>
#include <ios>
#include <ostream>
#include <string>
namespace seneca {
  size_t Station::m_widthField{0};
  size_t Station::id_generator{0};

  Station::Station(const std::string& str) {
    Utilities u;
    size_t pos = 0;
    bool more = false;
    this->m_id = ++id_generator;
    this->m_name = u.extractToken(str, pos, more);
    
    if (u.getFieldWidth() > this->m_widthField) {
      this->m_widthField = u.getFieldWidth();
    }

    this->m_nextSerialNumber = std::stoull(u.extractToken(str, pos, more));
    this->m_quantity = std::stoull(u.extractToken(str, pos, more));
    this->m_desc = u.extractToken(str, pos, more);
    
  }

  const std::string& Station::getItemName() const {
    return this->m_name;
  }

  size_t Station::getNextSerialNumber() {
    return this->m_nextSerialNumber++;
  }

  size_t Station::getQuantity() const {
    return this->m_quantity;
  }

  void Station::updateQuantity() {
    if (this->m_quantity == 0) {
      return;
    }
    this->m_quantity--;
  }

  void Station::display(std::ostream& os, bool full) const {
    os << std::setw(3) << std::setfill('0');
    os << this->m_id;
    os << " | " << std::setfill(' ');
    os << std::setw(this->m_widthField);
    os << std::setiosflags(std::ios_base::left);
    os << this->m_name;
    os << std::resetiosflags(std::ios_base::left);
    os << " | ";
    os << std::setw(6) << std::setfill('0');
    os << this->m_nextSerialNumber;
    os << " | " << std::setfill(' ');
    if (full) {
      os << std::setw(4);
      os << this->m_quantity;
      os << " | ";
      os << this->m_desc;
    }
    os << "\n";
  }
}
