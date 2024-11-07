// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca
// date: 6/11/2024
// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <cstdint>
namespace seneca {

  struct Settings {
    int16_t m_maxSummaryWidth{80};
    bool m_tableView{false};
  };

  extern Settings g_settings; 
}

#endif  // SENECA_SETTINGS_H
