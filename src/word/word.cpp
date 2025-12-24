#include "word.hpp"
#include "../utils/utils.hpp"
#include <cassert>

namespace Wordle
{
    Word::Word(const std::string& word)
    : m_baseWord(toLowerCase(word))
    {
        // Ensure the word length is correct
        assert(m_baseWord.length() == WORD_LENGTH);

        // Initialize m_letterCount to zero
        std::fill(m_letterCount, m_letterCount + ALPHABET_SIZE, 0);

        // fill in the data in the other arrays
        for (std::size_t i = 0; i < WORD_LENGTH; ++i)
        {
            Letter letterRepresentation = charToInt(m_baseWord[i]);
            m_letters[i] = letterRepresentation;
            m_letterCount[letterRepresentation]++;
        }
    }

    Word& Word::operator=(const Word& other)
    {
        if (this != &other)
        {
            // Copy base_word (const_cast needed for const member)
            const_cast<std::string&>(m_baseWord) = other.m_baseWord;
            
            // Copy letters array
            for (std::size_t i = 0; i < WORD_LENGTH; ++i)
                m_letters[i] = other.m_letters[i];
            
            
            // Copy letter_count array
            for (std::size_t i = 0; i < ALPHABET_SIZE; ++i)
                m_letterCount[i] = other.m_letterCount[i];
            
        }
        return *this;
    }
} // namespace Wordle
