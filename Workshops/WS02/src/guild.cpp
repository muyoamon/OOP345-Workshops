// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 1/10/2024
#include "guild.h"
#include "character.h"
#include <iomanip>
#include <iostream>
#include <utility>
namespace seneca {
  Guild::Guild() : m_name{}, m_members{nullptr}, m_size{0}, m_allocSize{0} {}
  Guild::Guild(const char* name) : m_name(name), m_members{nullptr}, 
    m_size{0}, m_allocSize{0} {}
  Guild::~Guild() {
    delete[] m_members;
  }
  void Guild::swap(Guild& other) noexcept {
    std::swap(m_members, other.m_members);
    m_name.swap(other.m_name);
    std::swap(m_size, other.m_size);
    std::swap(m_allocSize, other.m_allocSize);
  }
  Guild::Guild(Guild& rhs) : m_name{rhs.m_name}, m_allocSize{0} {
    m_size = rhs.m_size;
    m_members = new Character*[m_size]();
    for (size_t i = 0; i < rhs.m_size; i++) {
      m_members[i] = rhs.m_members[i];
    }
  }
  Guild::Guild(Guild&& rhs) noexcept : Guild() {
    this->swap(rhs);
	}
  Guild& Guild::operator=(Guild& rhs) {
    Guild temp(rhs);
    this->swap(temp);
    return *this;
	}
  Guild& Guild::operator=(Guild&& rhs) noexcept {
    this->swap(rhs);
    return *this;
	}

  void Guild::addMember(Character* c) {
    for (size_t i = 0; i < m_size; i++) {
      if (m_members[i]->getName() == c->getName()) {
        // exit function
        return;
      }
    }

    // array is full
    if (m_size == m_allocSize) {
      if (m_allocSize == 0) {
        m_allocSize = 2;
        m_members = new Character*[m_allocSize]();
      } else { 
        // allocate twice the size of original array
        Character** temp = new Character*[m_allocSize *= 2](); // value-initialize
        for (size_t i = 0; i < m_size; i++) {
          temp[i] = m_members[i]; // move the Character*
          m_members[i] = nullptr; // prevent double free
        }
        delete[] m_members;
        m_members = temp;
      }
    }
    m_members[m_size] = c;
    c->setHealthMax(c->getHealthMax() + 300);
    c->setHealth(c->getHealthMax());
    m_size++;
	}
  void Guild::removeMember(const std::string& c) {
	  for (size_t i = 0; i < m_size; i++) {
      if (m_members[i]->getName() == c) {
        m_members[i]->setHealth(m_members[i]->getHealth() - 300);
        m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
        // shift left
        for (size_t j = i; j < m_size - 1; j++) {
          m_members[j] = m_members[j + 1];
        }
        m_members[m_size - 1] = nullptr;
        m_size--;
      }
    }
  }

  Character* Guild::operator[](size_t idx) const {
    if (idx < m_size) {
      return m_members[idx];
    }
    return nullptr;
	}
  void Guild::showMembers() const {
    if (m_name == "") {
      std::cout << "No guild.\n";
      return;
    }
    std::cout << "[Guild] " << m_name << "\n";
    for (size_t i = 0; i < m_size; i++) {
      std::cout << std::setw(5) << i+1 << ": "<< *m_members[i] << "\n";
    }

	}
  
}
