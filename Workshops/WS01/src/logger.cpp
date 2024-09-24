// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 24/09/2024
#include "logger.h"
#include "event.h"
#include <cstddef>
#include <cstring>
#include <iostream>
namespace seneca {
  Logger::Logger(): m_size(0), m_events(nullptr), m_end(nullptr) {}
  Logger::~Logger() {
    delete[] m_events;
  }
  Logger& Logger::operator=(Logger&& l) {
    this->m_events = new Event[l.m_size];
    this->m_size = l.m_size;
    for (size_t i=0; i<m_size;i++) {
      m_events[i] = l.m_events[i];
    }
    return *this;
  }
  void Logger::addEvent(const Event& event) {
    static size_t pos = 0;
    if (pos == m_size) {
      if (pos == 0) { //uninitailized
        m_events = new Event[4]();
        m_size = 4;
      } else {   //realloc
        Event* tmpPtr = new Event[m_size*2] ();
        for (size_t i=0; i<m_size;i++) {
          tmpPtr[i] = m_events[i];
        }
        delete[] m_events;
        m_events = tmpPtr;
        m_size *= 2;
      }
    }
    m_events[pos] = event;
    pos++;
    m_end = m_events+pos;
  }
  std::ostream& operator<<(std::ostream& ostr, const Logger& l) {
    for (Event* i=l.m_events;i!=l.m_end;i++) {
      std::cout << *i << std::endl;
    }
    return ostr;
  }
  
}
