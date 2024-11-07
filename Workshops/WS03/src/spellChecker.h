// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <vector>
namespace seneca {
class SpellChecker {
  std::string m_badWords[6];
  std::string m_goodWords[6];
  size_t m_count[6];
  public:
  SpellChecker(const char* filename);
  void operator()(std::string& text);
  void showStatistics(std::ostream& out) const;
};
}

#endif  // SENECA_SPELLCHECKER_H
