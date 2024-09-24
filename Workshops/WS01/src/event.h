// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 24/09/2024
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <chrono>
#include <string>
namespace seneca {
  class Event {
    std::string m_name;
    std::chrono::nanoseconds m_duration;
    public:
    Event();
    Event(const char* name, const std::chrono::nanoseconds& duration);
    friend std::ostream& operator<<(std::ostream&, const Event&);
  };
}

#endif // !SENECA_EVENT_H

