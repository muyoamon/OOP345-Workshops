// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include <array>
#include <list>
#include <string>
#include <vector>
namespace seneca {

class TvShow : public MediaItem {
  struct TvEpisode {
    const TvShow *m_show{};
    unsigned short m_numberOverall{};
    unsigned short m_season{};
    unsigned short m_numberInSeason{};
    std::string m_airDate{};
    unsigned m_length{};
    std::string m_title{};
    std::string m_summary{};
  };

  std::string m_id;
  std::vector<TvEpisode> m_episodes;

  template <typename T>
  TvShow(T &container)
      : MediaItem(container[1], container[3], std::stoi(container[2])), m_id{container[0]} {}

public:
  void display(std::ostream &out) const override;
  static TvShow *createItem(const std::string &strShow);

  template <typename Collection_T>
  static void addEpisode(Collection_T &col, const std::string &strEpisode) {
    std::array<std::string, 8> argsArr{};
    if (strEpisode == "") {
      throw "Not a valid Episode.";
    }
    if (strEpisode[0] == '#') {
      throw "Not a valid Episode.";
    }
    size_t current = 0u;
    size_t next = strEpisode.find(",");
    for (auto i = 0u; i < argsArr.size() - 1; i++) {
      argsArr[i] = strEpisode.substr(current, next - current);
      current = next + 1;
      next = strEpisode.find(",", next + 1);
      trim(argsArr[i]);
    }
    argsArr[argsArr.size() - 1] = strEpisode.substr(current);
    trim(argsArr[argsArr.size() - 1]);
    unsigned length = std::stoi(argsArr[5])*3600 + std::stoi(argsArr[5].substr(3))*60 + std::stoi(argsArr[5].substr(6));


    TvEpisode episode;
    episode.m_numberOverall = std::stoi(argsArr[1]);
    episode.m_season = argsArr[2] == "" ? 1 : std::stoi(argsArr[2]);
    episode.m_numberInSeason = std::stoi(argsArr[3]);
    episode.m_airDate = argsArr[4];
    episode.m_length = length;
    episode.m_title = argsArr[6];
    episode.m_summary = argsArr[7];

    for (auto i = 0u; i<col.size(); i++) {
      if (TvShow* pEpisode = dynamic_cast<TvShow*>(col[i])) {
        if (pEpisode->m_id == argsArr[0]) {
          episode.m_show = pEpisode;
          pEpisode->m_episodes.push_back(episode);
          return;
        }
      }
    }
  }
  double getEpisodeAverageLength() const;
  std::list<std::string> getLongEpisodes() const;
};

} // namespace seneca

#endif // SENECA_TVSHOW_H
