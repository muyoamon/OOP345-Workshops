// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 1/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "Utilities.h"
#include <cctype>
#include <exception>
#include <string>
namespace seneca {

char Utilities::m_delimiter{','};

static std::string trim(const std::string &str) {
  std::string res;
  size_t lastChar = std::string::npos;
  for (size_t i = 0; i < str.size(); i++) {
    if (isspace(str[i]) && lastChar == std::string::npos) {
      // do nothing
      continue;
    }
    res += str[i];
    if (!isspace(str[i])) lastChar = res.size();
  }
  if (res == "") return res;
  return res.substr(0, lastChar);
}

void Utilities::setFieldWidth(size_t newWidth) {
  this->m_widthField = newWidth;
}
size_t Utilities::getFieldWidth() { return this->m_widthField; }
std::string Utilities::extractToken(const std::string &str, size_t &next_pos,
                                    bool &more) {
  std::string res;
  if (str[next_pos] == this->m_delimiter) {
    more = false;
    throw std::exception();
  }
  auto find = str.find(this->m_delimiter, next_pos);
  if (find == std::string::npos) {
    more = false;
    res = trim(str.substr(next_pos));
    next_pos = str.size();
  } else {
    more = true;
    res = trim(str.substr(next_pos, find - next_pos));
    next_pos = find + 1;
  }
  if (next_pos >= str.size()) {
    more = false;
  }
  if (res.size() > this->m_widthField) {
    this->m_widthField = res.size();
  }

  return res;
}

void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }
char Utilities::getDelimiter() { return m_delimiter; }

} // namespace seneca
