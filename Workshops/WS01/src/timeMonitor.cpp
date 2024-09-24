// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 24/09/2024
#include "timeMonitor.h"
#include "event.h"
#include <chrono>

namespace seneca {
  void TimeMonitor::startEvent(const char* name) {
    m_name = name;
    m_startTime = std::chrono::system_clock::now();
  }

  Event TimeMonitor::stopEvent() {
    m_stopTime = std::chrono::system_clock::now();
    std::chrono::nanoseconds duration = m_stopTime - m_startTime;
    return Event(m_name.c_str(),duration);
  }
}
