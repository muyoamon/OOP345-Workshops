// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 1/10/2024
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
namespace seneca  {
  
  template <typename T>
  class CharacterTpl : public Character {
    int m_healthMax;
    T m_health;
  public:
    CharacterTpl(const char* name, int maxHealth)
    : Character(name), m_healthMax{maxHealth} {
      m_health = m_healthMax;  
    }

    
    void takeDamage(int dmg) {
      m_health -= dmg;
      m_health = (m_health < 0) ? 0 : m_health;
      if (!this->isAlive()) {
        std::cout << "    "<< getName() << " has been defeated!\n"; 
      } else {
        std::cout << "    " << getName() << " took " << dmg << " damage, " << m_health << " health remaining.\n";
      }
    }

    
    int getHealth() const {
      return static_cast<int>(m_health);
    }
    
    int getHealthMax() const {
      return m_healthMax;
    }
    
    void setHealth(int health) {
      m_health = health;
    }
    
    void setHealthMax(int health) {
      m_healthMax = health;
    }
  };
}

#endif // !SENECA_CHARACTERTPL_H;
