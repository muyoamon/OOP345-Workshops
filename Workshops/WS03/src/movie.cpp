// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "movie.h"
#include "mediaItem.h"
#include "settings.h"
#include <array>
#include <iomanip>
namespace seneca {
void Movie::display(std::ostream &out) const {
  if (g_settings.m_tableView) {
    out << "M | ";
    out << std::left << std::setfill('.');
    out << std::setw(50) << this->getTitle() << " | ";
    out << std::right << std::setfill(' ');
    out << std::setw(9) << this->getYear() << " | ";
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
    out << this->getTitle() << " [" << this->getYear() << "]\n";
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

Movie* Movie::createItem(const std::string& strMovie) {
  std::array<std::string, 3> argsArr{};
  if (strMovie == "") {
    throw "Not a valid movie.";
    return nullptr;
  }
  if (strMovie[0] == '#') {
    throw "Not a valid movie.";
    return nullptr;
  }
  size_t current = 0u;
  size_t next = strMovie.find(",");
  for (auto i = 0u; i < argsArr.size() - 1; i++) {
    argsArr[i] = strMovie.substr(current, next - current);
    current = next + 1;
    next = strMovie.find(",", next + 1);
    trim(argsArr[i]);
  }
  argsArr[argsArr.size() - 1] = strMovie.substr(current);
  trim(argsArr[argsArr.size() - 1]);

  return new Movie(argsArr);

}
} // namespace seneca
