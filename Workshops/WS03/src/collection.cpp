// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "collection.h"
#include "mediaItem.h"
#include <algorithm>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>
namespace seneca {

static std::string trimQuotation(const std::string &str) {
  auto res = str;
  if (res.empty()) {
    return std::string();
  }
  if (res.front() == '"') {
    res.erase(0, 1);
  }
  if (res.back() == '"') {
    res.erase(res.size() - 1);
  }
  return res;
}

Collection::Collection(const std::string &name)
    : m_name{name}, m_observer(nullptr) {}

Collection::~Collection() {
  for (auto &i : m_container) {
    delete i;
  }
}

size_t Collection::size() const { return m_container.size(); }

void Collection::setObserver(void (*observer)(const Collection &,
                                              const MediaItem &)) {
  m_observer = observer;
}

Collection &Collection::operator+=(MediaItem *item) {
  auto idx = (*this)[item->getTitle()];
  if (idx == item) {
    return *this;
  }
  if (idx != nullptr) {
    delete item;
    return *this;
  }
  m_container.push_back(item);
  if (m_observer != nullptr) {
    m_observer(*this, *item);
  }
  return *this;
}

MediaItem *Collection::operator[](size_t idx) const {
  if (idx > m_container.size()) {
    throw std::out_of_range("Bad index " + std::to_string(idx) +
                            ". Collection has " + std::to_string(this->size()) +
                            " items.");
    return nullptr;
  }
  return m_container[idx];
}

MediaItem *Collection::operator[](const std::string &title) const {
  auto it = std::find_if(
      m_container.begin(), m_container.end(),
      [title](MediaItem *ptr) { return title == ptr->getTitle(); });
  return it != m_container.end() ? (*it) : nullptr;
}

void Collection::removeQuotes() {
  std::for_each(m_container.begin(), m_container.end(), [](MediaItem *ptr) {
    ptr->setTitle(trimQuotation(ptr->getTitle()));
    ptr->setSummary(trimQuotation(ptr->getSummary()));
  });
}

void Collection::sort(const std::string &field) {
  if (field == "title") {
    std::sort(m_container.begin(), m_container.end(),
              [](MediaItem *p, MediaItem *q) {
                return p->getTitle() < q->getTitle();
              });
  } else if (field == "year") {
    std::sort(
        m_container.begin(), m_container.end(),
        [](MediaItem *p, MediaItem *q) { return p->getYear() < q->getYear(); });
  }
}

std::ostream &operator<<(std::ostream &ostr, const Collection &collection) {
  for (auto i = 0u; i < collection.size(); i++) {
    ostr << *collection[i];
  }
  return ostr;
}

} // namespace seneca
