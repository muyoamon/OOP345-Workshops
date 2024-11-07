// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "tvShow.h"
#include "settings.h"
#include <algorithm>
#include <array>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <ostream>
#include <string>
#include <vector>
namespace seneca {
void TvShow::display(std::ostream &out) const {
  if (g_settings.m_tableView) {
    out << "S | ";
    out << std::left << std::setfill('.');
    out << std::setw(50) << this->getTitle() << " | ";
    out << std::right << std::setfill(' ');
    out << std::setw(2) << this->m_episodes.size() << " | ";
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
    out << this->getTitle() << " [" << this->getYear() << "]\n";
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
        << '\n';
    while (pos < this->getSummary().size()) {
      out << "    "
          << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth)
          << '\n';
      pos += g_settings.m_maxSummaryWidth;
    }
    for (auto &item : m_episodes) {
      out << std::setfill('0') << std::right;
      out << "    " << 'S' << std::setw(2) << item.m_season << 'E'
          << std::setw(2) << item.m_numberInSeason << ' ';
      if (item.m_title != "")
        out << item.m_title << '\n';
      else
        out << "Episode " << item.m_numberOverall << '\n';

      pos = 0;
      while (pos < item.m_summary.size()) {
        out << "            "
            << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8)
            << '\n';
        pos += g_settings.m_maxSummaryWidth - 8;
      }
    }
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
        << std::setfill(' ') << '\n';
  }
}
TvShow *TvShow::createItem(const std::string &strShow) {
  std::array<std::string, 4> argsArr{};
  if (strShow == "") {
    throw "Not a valid show.";
    return nullptr;
  }
  if (strShow[0] == '#') {
    throw "Not a valid show.";
    return nullptr;
  }
  size_t current = 0u;
  size_t next = strShow.find(",");
  for (auto i = 0u; i < argsArr.size() - 1; i++) {
    argsArr[i] = strShow.substr(current, next - current);
    current = next + 1;
    next = strShow.find(",", next + 1);
    trim(argsArr[i]);
  }
  argsArr[argsArr.size() - 1] = strShow.substr(current);
  trim(argsArr[argsArr.size() - 1]);

  return new TvShow(argsArr);
}

double TvShow::getEpisodeAverageLength() const {
  return std::accumulate(this->m_episodes.begin(), this->m_episodes.end(),
                         (double)0,
                         [](double sum, const TvEpisode &episode) {
                           return sum + episode.m_length;
                         }) /
         this->m_episodes.size();
}

std::list<std::string> TvShow::getLongEpisodes() const {
  std::vector<TvEpisode> episodes;

  std::copy_if(this->m_episodes.begin(), this->m_episodes.end(),
               std::back_inserter(episodes), [](const TvEpisode &episode) {
                 return episode.m_length >= 3600;
               });

  std::list<std::string> episodesList;

  std::transform(episodes.begin(), episodes.end(),
                 std::back_inserter(episodesList),
                 [](const TvEpisode &episode) { return episode.m_title; });
  return episodesList;
}

} // namespace seneca
