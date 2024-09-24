// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 24/09/2024
#include "event.h"
#include "settings.h"
#include <chrono>
#include <iomanip>
#include <ostream>

namespace seneca {
  Event::Event()
    : m_name(""), m_duration(0){}
  
  Event::Event(const char* name, const std::chrono::nanoseconds& duration)
  : m_name(name), m_duration(duration) {}

  std::ostream& operator<<(std::ostream& ostr, const Event& event) {
    static size_t counter = 1;
    ostr << std::setw(2) << counter++ << ": ";
    ostr << std::setw(40) << event.m_name << " -> ";
    int duration_width = 0;
    if (g_settings.m_time_units == "seconds") {
      duration_width = 2;
      ostr << std::setw(duration_width) << std::chrono::duration_cast<std::chrono::seconds>(event.m_duration).count();
    } else if (g_settings.m_time_units == "milliseconds") {
      duration_width = 5;
      ostr << std::setw(duration_width) << std::chrono::duration_cast<std::chrono::milliseconds>(event.m_duration).count();
    } else if (g_settings.m_time_units == "microseconds") {
      duration_width = 8;
      ostr << std::setw(duration_width) << std::chrono::duration_cast<std::chrono::microseconds>(event.m_duration).count();
    } else if (g_settings.m_time_units == "nanoseconds") {
      duration_width = 11;
      ostr << std::setw(duration_width) << event.m_duration.count();
    }
    ostr << " " << g_settings.m_time_units;
    return ostr;
  }
}
