// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "mediaItem.h"
#include <ostream>
namespace seneca {
class Movie : public MediaItem {
  template <typename T>
  Movie(T& container) : MediaItem(container[0], container[2], std::stoi(container[1])) {}
public:
  void display(std::ostream &) const override;
  static Movie* createItem(const std::string&);
};
} // namespace seneca

#endif // SENECA_MOVIE_H
