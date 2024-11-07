// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "book.h"
#include "mediaItem.h"
#include "settings.h"
#include <array>
#include <iomanip>
#include <ostream>
namespace seneca {

Book::Book(const std::string &author, const std::string &title,
           const std::string &country, const double price,
           const unsigned short year, const std::string &summary)
    : MediaItem(title, summary, year), m_author{author}, m_country{country},
      m_price{price} {}
void Book::display(std::ostream &out) const {
  if (g_settings.m_tableView) {
    out << "B | ";
    out << std::left << std::setfill('.');
    out << std::setw(50) << this->getTitle() << " | ";
    out << std::right << std::setfill(' ');
    out << std::setw(2) << this->m_country << " | ";
    out << std::setw(4) << this->getYear() << " | ";
    out << std::left;
    if (g_settings.m_maxSummaryWidth > -1) {
      if (static_cast<short>(this->getSummary().size()) <=
          g_settings.m_maxSummaryWidth)
        out << this->getSummary();
      else
        out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3)
            << "...";
    } else
      out << this->getSummary();
    out << std::endl;
  } else {
    size_t pos = 0;
    out << this->getTitle() << " [" << this->getYear() << "] [";
    out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
        << '\n';
    while (pos < this->getSummary().size()) {
      out << "    "
          << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth)
          << '\n';
      pos += g_settings.m_maxSummaryWidth;
    }
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
        << std::setfill(' ') << '\n';
  }
}

Book *Book::createItem(const std::string &strBook) {
  std::array<std::string, 6> argsArr{};
  if (strBook == "") {
    throw "Not a valid book.";
    return nullptr;
  }
  if (strBook[0] == '#') {
    throw "Not a valid book.";
    return nullptr;
  }
  size_t current = 0u;
  size_t next = strBook.find(",");
  for (auto i = 0u; i < argsArr.size() - 1; i++) {
    argsArr[i] = strBook.substr(current, next - current);
    current = next + 1;
    next = strBook.find(",", next + 1);
    trim(argsArr[i]);
  }
  argsArr[argsArr.size() - 1] = strBook.substr(current);
  trim(argsArr[argsArr.size() - 1]);

  return new Book(argsArr);
}
} // namespace seneca
