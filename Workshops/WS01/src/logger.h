#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"
#include <chrono>
#include <ostream>
#include <string>
namespace seneca {
  class Logger {
    size_t m_size;
    Event* m_events;
    Event* m_end; // pointer to end of the event array (similar to vector.end())
    public:
      Logger(const Logger&) = delete;
      Logger& operator=(const Logger&) = delete;

      Logger();
      ~Logger();
      Logger& operator=(Logger&&);
      void addEvent(const Event& event);
      friend std::ostream& operator<<(std::ostream&, const Logger&);
  };
}

#endif // !SENECA_LOGGER_H

