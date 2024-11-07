// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "spellChecker.h"
#include <fstream>
#include <iomanip>
#include <ostream>
namespace seneca {
SpellChecker::SpellChecker(const char *filename) : m_count{0} {
  std::fstream fs(filename);
  if (!fs) {
    throw "Bad file name!";
  }
  for (auto i = 0u; i<6;i++) {
    fs >> m_badWords[i] >> m_goodWords[i];
  }
}

void SpellChecker::operator()(std::string& text) {
  for (auto i = 0u;i < 6; i++) {
    size_t pos = 0;
    while((pos = text.find(m_badWords[i])) != std::string::npos) {
      text.replace(pos, m_badWords[i].size(), m_goodWords[i]);
      m_count[i] ++;
    }
  }
}

void SpellChecker::showStatistics(std::ostream& out) const {
  out << "Spellchecker Statistics\n";
  for (auto i = 0u; i < 6; i++) {
    out << std::setw(15) << m_badWords[i] << ": " << m_count[i] << " replacements\n";
  }
}

} // namespace seneca
