// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 1/10/2024
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h"
namespace seneca {
  template <typename T, class FirstAbility_t, class SecondAbility_t>
  class Rogue : public CharacterTpl<T> {
    int m_baseAttack;
    int m_baseDefense;
    FirstAbility_t m_firstAbility;
    SecondAbility_t m_secondAbility;
    Dagger m_weapon;
  public: 
    Rogue(const char* name, int healthMax, int baseAttack, 
        int baseDefense)
        : CharacterTpl<T>(name, healthMax), m_baseAttack{baseAttack}, m_baseDefense{baseDefense} {}
    
    
    int getAttackAmnt() const {
      return static_cast<int>(m_baseAttack + 2 * static_cast<double>(m_weapon));
    }

      
    int getDefenseAmnt() const {
      return m_baseDefense;
    }

    
    Character* clone() const {
      return new Rogue<T, FirstAbility_t, SecondAbility_t>(this->getName().c_str(),this->getHealthMax(),
          m_baseAttack, m_baseDefense);
    }

    
    void attack(Character* enemy) {
      std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
      m_firstAbility.useAbility(this);
      m_secondAbility.useAbility(this);
      int attackAmnt = getAttackAmnt();
      m_firstAbility.transformDamageDealt(attackAmnt);
      m_secondAbility.transformDamageDealt(attackAmnt);
      std::cout << "    Rogue deals " << attackAmnt << " melee damage!\n";
      enemy->takeDamage(attackAmnt);
    }

    
    void takeDamage(int dmg) {
      std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
      std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received.\n";
      int damage = (dmg - m_baseDefense > 0) ? dmg - m_baseDefense : 0;
      m_firstAbility.transformDamageReceived(damage);
      m_secondAbility.transformDamageReceived(damage);
      this->CharacterTpl<T>::takeDamage(damage);
	  }
  };
}

#endif // !SENECA_ROGUE_H

