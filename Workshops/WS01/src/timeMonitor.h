// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 24/09/2024
#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include "event.h"
#include <chrono>
#include <string>
namespace seneca {
  class TimeMonitor {
    std::string m_name;
    std::chrono::time_point<std::chrono::system_clock> m_startTime;
    std::chrono::time_point<std::chrono::system_clock> m_stopTime;
    public:
      void startEvent(const char* name);
      Event stopEvent();
  };
}

#endif // !SENECA_TIMEMONITOR_H

