// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 8/12/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#include "LineManager.h"
#include "Utilities.h"
#include "Workstation.h"
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <ostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
namespace seneca {
  LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
    Utilities u;
    std::unordered_map<Workstation*, std::string> nextItemMap;
    std::set<std::string> nextItemSet;
    std::unordered_map<std::string, Workstation*> stationMap;
    std::ifstream f(file);
    std::string line;
    while (std::getline(f, line)) {
      size_t pos = 0;
      bool more = true;
      std::string itemName = u.extractToken(line, pos, more);
      Workstation* pWorkStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* elem){
          return elem->getItemName() == itemName;
          });
      m_activeLine.push_back(pWorkStation);
      stationMap[itemName] = pWorkStation;
      if (!more) {
        nextItemMap[pWorkStation] = "";
      } else {
        auto nextItem = u.extractToken(line, pos, more);
        nextItemMap[pWorkStation] = nextItem;
        nextItemSet.insert(nextItem);
      }
    };

    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* elem){
        if (nextItemMap[elem] == "") {
          return;
        }
          elem->setNextStation(stationMap[nextItemMap[elem]]);
        });
    
    m_firstStation = *std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* elem){
      return nextItemSet.find(elem->getItemName()) == nextItemSet.end();
        });
    m_cntCustomerOrder = g_pending.size();
  }

  void LineManager::reorderStations() {
    std::vector<Workstation*> res;
    Workstation* next = m_firstStation;
    while (next) {
      res.push_back(next);
      next = next->getNextStation();
    }
    m_activeLine = res;
  }

  bool LineManager::run(std::ostream& os) {
    static size_t iteration = 1;
    os << "Line Manager Iteration: " << iteration << std::endl;
    if (!g_pending.empty()) {
      *m_firstStation += std::move(g_pending.front());
      g_pending.pop_front();
    }
    for (auto& station: m_activeLine) {
      station->fill(os);
    }
    for (auto& station: m_activeLine) {
      station->attempToMoveOrder();
    }
    iteration++;
    if (g_incomplete.size() + g_completed.size() == m_cntCustomerOrder) {
      return true;
    } else {
      return false;
    }
  }

  void LineManager::display(std::ostream& os) const {
    for (auto& i:m_activeLine) {
      i->display(os);
    }
  }
}


