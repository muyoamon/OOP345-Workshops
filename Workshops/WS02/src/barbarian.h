#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "character.h"
#include "characterTpl.h"
namespace seneca  {
  template<typename T, class Ability_t, class Weapon_t>
  class Barbarian : public CharacterTpl<T> {
    int m_baseAttack;
    int m_baseDefense;
    Ability_t m_ability;
    Weapon_t m_weapon[2];
  public:
   
  Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, 
        Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
        : CharacterTpl<T>(name, healthMax), m_baseAttack{baseAttack}, 
    m_baseDefense{baseDefense}, m_weapon{primaryWeapon, secondaryWeapon} {}
  
  int getAttackAmnt() const {
    return static_cast<int>(m_baseAttack + 
        static_cast<double>(m_weapon[0])/2 + static_cast<double>(m_weapon[1])/2);
	}
  
  int getDefenseAmnt() const {
    return m_baseDefense;
	}
  
  Character* clone() const {
    return new Barbarian<T, Ability_t, Weapon_t>(this->getName().c_str(),this->getHealthMax(),
        m_baseAttack, m_baseDefense, m_weapon[0], m_weapon[1]);
	}
  
  void attack(Character* enemy) {
    std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
    m_ability.useAbility(this);
    int attackAmnt = getAttackAmnt();
    m_ability.transformDamageDealt(attackAmnt);
    std::cout << "    Barbarian deals " << attackAmnt << " melee damage!\n";
    enemy->takeDamage(attackAmnt);
	}

  
  void takeDamage(int dmg) {
    std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
    std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received.\n";
    int damage = (dmg - m_baseDefense > 0) ? dmg - m_baseDefense : 0;
    m_ability.transformDamageReceived(damage);
    this->CharacterTpl<T>::takeDamage(damage);
	}
  };
}

#endif // !SENECA_BARBARIAN_H
