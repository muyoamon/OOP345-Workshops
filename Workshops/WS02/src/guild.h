// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 1/10/2024
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <string>
namespace seneca {
  class Guild {
    std::string m_name;
    Character** m_members;
    size_t m_size;
    size_t m_allocSize; // allocated size

  public:
    Guild();
    Guild(const char* name);
    ~Guild();
    Guild(Guild&);
    Guild(Guild&&) noexcept;
    Guild& operator=(Guild&);
    Guild& operator=(Guild&&) noexcept;

    // for copy-swap idiom
    void swap(Guild& other) noexcept;
    
    void addMember(Character* c);
    void removeMember(const std::string& c);

    Character* operator[](size_t idx) const;
    void showMembers() const;
  };
}

#endif // !SENECA_GUILD_H

