#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>
namespace seneca {
  class Team {
    std::string m_name;
    Character** m_members;
    size_t m_size;
    size_t m_allocSize; // allocated size

  public:
    Team();
    Team(const char* name);
    ~Team();
    Team(Team&);
    Team(Team&&) noexcept;
    Team& operator=(Team&);
    Team& operator=(Team&&) noexcept;

    // for copy-swap idiom
    void swap(Team& other) noexcept;
    
    void addMember(const Character* c);
    void removeMember(const std::string& c);

    Character* operator[](size_t idx) const;
    void showMembers() const;
  };
}

#endif // !SENECA_TEAM_H

