// name: Thanatorn Wongthanaporn
// id: 161197223
// email: twongthanaporn@myseneca.ca 
// date: 24/09/2024
#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>
namespace seneca {
  enum class PartOfSpeech {
    Unknown,
    Noun,
    Pronoun,
    Adjective,
    Adverb,
    Verb,
    Preposition,
    Conjunction,
    Interjection,
  };

  struct Word {
    std::string m_word{};
    std::string m_definition{};
    PartOfSpeech m_pos = PartOfSpeech::Unknown;
  };

  class Dictionary {
    Word* m_words;
    size_t m_length;

    void swap(Dictionary& rhs);
    public:
      Dictionary();
      Dictionary(const char* filename);
      Dictionary(const Dictionary&);
      Dictionary(Dictionary&&);
      ~Dictionary();
      Dictionary& operator=(const Dictionary&);
      Dictionary& operator=(Dictionary&&);
      void searchWord(const char* word);

  };

  std::ostream& operator<<(std::ostream&, const PartOfSpeech&);
}

#endif // !SENECA_DICTIONARY_H

