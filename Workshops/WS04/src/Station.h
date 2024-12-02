// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 1/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>
namespace seneca {
class Station {
  int m_id;
  std::string m_name;
  std::string m_desc;
  size_t m_nextSerialNumber;
  size_t m_quantity;

  static size_t m_widthField;
  static size_t id_generator;

  public:
  Station(const std::string&);
  const std::string& getItemName() const;
  size_t getNextSerialNumber();
  size_t getQuantity() const;
  void updateQuantity();
  void display(std::ostream&, bool full) const;

};
}

#endif  // SENECA_STATION_H
