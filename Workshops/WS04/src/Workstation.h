// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 8/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include "CustomerOrder.h"
#include <deque>
#include <ostream>
#include <string>

namespace seneca {
  
extern std::deque<CustomerOrder> g_pending;
extern std::deque<CustomerOrder> g_completed;
extern std::deque<CustomerOrder> g_incomplete;

class Workstation : public Station {
  std::deque<CustomerOrder> m_orders;
  Workstation* m_pNextStation;
  public:
  Workstation(const std::string&);
  void fill(std::ostream& os);
  bool attempToMoveOrder();
  void setNextStation(Workstation*);
  Workstation* getNextStation() const;
  void display(std::ostream&) const;
  Workstation& operator+=(CustomerOrder&& newOrder);


};

}

#endif  // SENECA_WORKSTATION_H
