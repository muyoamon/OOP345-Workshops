#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
namespace seneca {
  template <class Weapon_t>
  class Archer : public CharacterTpl<seneca::SuperHealth> {
    int m_baseAttack;
    int m_baseDefense;
    Weapon_t m_weapon;
    public:
    Archer(const char* name, int healthMax, int baseAttack, 
      int baseDefense, Weapon_t weapon)
      : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseAttack{baseAttack},
      m_baseDefense{baseDefense}, m_weapon{weapon} {}
    int getAttackAmnt() const {
      return static_cast<int>(1.3 * m_baseAttack);
	  }
    Character* clone() const {
      return new Archer<Weapon_t>(this->getName().c_str(),this->getHealthMax(),
        m_baseAttack, m_baseDefense, m_weapon);
	  }
    void attack(Character* enemy) {
      std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
      int attackAmnt = getAttackAmnt();
      std::cout << "    Archer deals " << attackAmnt << " range damage!\n";
      enemy->takeDamage(attackAmnt);
	  }
    int getDefenseAmnt() const {
      return static_cast<int>(1.2 * m_baseDefense);
	  }
    void takeDamage(int dmg) {
      std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
      std::cout << "    Archer has a defense of " << m_baseDefense << ". Reducing damage received.\n";
      int damage = (dmg - m_baseDefense > 0) ? dmg - m_baseDefense : 0;
      this->CharacterTpl<seneca::SuperHealth>::takeDamage(damage);
    }
  };
}

#endif // !SENECA_ARCHER_H

