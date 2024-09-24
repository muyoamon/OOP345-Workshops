#include "dictionary.h"
#include "settings.h"
#include <cstddef>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>

namespace seneca {
  Dictionary::Dictionary(): m_words(nullptr), m_length(0) {}

  Dictionary::Dictionary(const char* filename) {
    std::ifstream ifs(filename);
    std::string line;
    std::string word, pos, definition;
    size_t count = 0;
    m_length = 0;
    // count line
    while(std::getline(ifs,line)) {
      m_length++;
    }

    m_words = new Word[m_length] ();
    
    // reset ifstream state
    ifs.clear();
    ifs.seekg(0,std::ios_base::beg);

    while (std::getline(ifs,line)) {
      // read logic
      size_t position = 0;
      position = line.find(',');
      word = line.substr(0,position);
      line.erase(0,position+1);
      position = line.find(',');
      pos = line.substr(0,position);
      line.erase(0,position+1);
      definition = line;
      
      PartOfSpeech p;
      if (pos == "n." || pos == "n. pl.") {
        p = PartOfSpeech::Noun;
      } else if (pos == "adv.") {
        p = PartOfSpeech::Adverb;
      } else if (pos == "a.") {
        p = PartOfSpeech::Adjective;
      } else if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.") {
        p = PartOfSpeech::Verb;
      } else if (pos == "prep.") {
        p = PartOfSpeech::Preposition;
      } else if (pos == "pron.") {
        p = PartOfSpeech::Pronoun;
      } else if (pos == "conj.") {
        p = PartOfSpeech::Conjunction;
      } else if (pos == "interj.") {
        p = PartOfSpeech::Interjection;
      } else {
        p = PartOfSpeech::Unknown;
      }

      m_words[count++] = {word,definition,p};
    }

  }

  void Dictionary::swap(Dictionary& rhs) {
    std::swap(this->m_length, rhs.m_length);
    std::swap(this->m_words, rhs.m_words);
  }

  Dictionary::Dictionary(const Dictionary& rhs): m_length(rhs.m_length) {
    m_words = new Word[m_length]();
    for (size_t i=0;i<m_length;i++) {
      m_words[i] = rhs.m_words[i];
    }
  }

  Dictionary::Dictionary(Dictionary&& rhs): Dictionary() {
    this->swap(rhs);
  }

  Dictionary& Dictionary::operator=(const Dictionary& rhs) {
    Dictionary temp(rhs);
    this->swap(temp);
    return *this;
  }

  Dictionary& Dictionary::operator=(Dictionary&& rhs) {
    this->swap(rhs);
    return *this;
  }

  void Dictionary::searchWord(const char* word) {
    unsigned short count = 0;
    size_t indexBuffer[64]{0};
    for (size_t i=0;i<m_length;i++) {
      if (m_words[i].m_word == word) {
        indexBuffer[count++] = i;
      }
    }
    if (count > 0) {
      unsigned short wordLength = strlen(word);
      std::cout << word << " - " << m_words[indexBuffer[0]].m_pos
        << m_words[indexBuffer[0]].m_definition << std::endl; 
      if (g_settings.m_show_all) {
        for (auto i=1;i<count;i++) {
          std::cout << std::string(wordLength, ' ') << " - "
            << m_words[indexBuffer[i]].m_pos << m_words[indexBuffer[i]].m_definition
            << std::endl;
        }
      }
    } else 
      std::cout << "Word '" << word << "' was not found in the dictionary.\n";
  }

  std::ostream& operator<<(std::ostream& ostr, const PartOfSpeech& pos) {
    if (!g_settings.m_verbose || pos == PartOfSpeech::Unknown) {
      // do nothing
    } else {
      switch (pos) {
        case PartOfSpeech::Noun: {
                                   ostr << "(noun) ";
                                   break;
                                 }
        case PartOfSpeech::Adverb: {
                                     ostr << "(adverb) ";
                                     break;
                                   }
        case PartOfSpeech::Adjective: {
                                        ostr << "(adjective) ";
                                        break;
                                      }
        case PartOfSpeech::Verb: {
                                   ostr << "(verb) ";
                                   break;
                                 }
        case PartOfSpeech::Preposition: {
                                          ostr << "(preposition) ";
                                          break;
                                        }
        case PartOfSpeech::Pronoun: {
                                      ostr << "(pronoun) ";
                                      break;
                                    }
        case PartOfSpeech::Conjunction: {
                                          ostr << "(conjuction) ";
                                          break;
                                        }
        case PartOfSpeech::Interjection: {
                                           ostr << "(interjection) ";
                                           break;
                                         }
        default: {
                   break;
                 }
      }
    }
      return ostr;
  }

  Dictionary::~Dictionary() {
    delete[] m_words;
  }


}
