// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 8/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include "Workstation.h"
#include <ostream>
#include <string>
#include <vector>
namespace seneca {
  class LineManager {
  std::vector<Workstation*> m_activeLine;
  size_t m_cntCustomerOrder;
  Workstation* m_firstStation;
  public:
    LineManager(const std::string& file,const std::vector<Workstation*>& stations);
    void reorderStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
  };
}

#endif  // SENECA_LINEMANAGER_H
