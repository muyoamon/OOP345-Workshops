// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include "mediaItem.h"
#include <iostream>
#include <string>
namespace seneca {

class Book : public MediaItem {
  std::string m_author;
  std::string m_country;
  double m_price;

  Book(const std::string &author, const std::string &title,
       const std::string &country, const double price,
       const unsigned short year, const std::string &summary);
  template <typename T>
  Book(const T &container)
      : Book(container[0], container[1], container[2], std::stod(container[3]),
             std::stoi(container[4]), container[5]) {}

public:
  void display(std::ostream &) const override;
  static Book *createItem(const std::string &strBook);
};

} // namespace seneca

#endif // SENECA_BOOK_H
