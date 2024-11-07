// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <ostream>
#include <string>
#include <vector>
#include "mediaItem.h"
namespace seneca {
class Collection {
  std::string m_name;
  std::vector<MediaItem*> m_container;
  void (*m_observer)(const Collection&, const MediaItem&); 
  public:
  Collection(const std::string& name);
  Collection(const Collection&) = delete;
  Collection(const Collection&&) = delete;
  Collection& operator=(const Collection&) = delete;
  Collection& operator=(const Collection&&) = delete;
  ~Collection();

  size_t size() const;
  void setObserver(void(const Collection&, const MediaItem&));
  Collection& operator+=(MediaItem* item);
  MediaItem* operator[](size_t idx) const;
  MediaItem* operator[](const std::string& title) const;
  void removeQuotes();
  void sort(const std::string& field);
};

std::ostream& operator<<(std::ostream&, const Collection&);
}

#endif  // SENECA_COLLECTION_H
