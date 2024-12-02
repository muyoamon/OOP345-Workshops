// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 1/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <cstddef>
#include <string>
namespace seneca {
class Utilities {
  size_t m_widthField{1};
  static char m_delimiter;
  public:
  void setFieldWidth(size_t);
  size_t getFieldWidth();
  std::string extractToken(const std::string&, size_t&, bool&);

  static void setDelimiter(char);
  static char getDelimiter();
};
}

#endif  // SENECA_UTILITIES_H
