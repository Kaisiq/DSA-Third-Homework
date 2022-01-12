#pragma once
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <forward_list>
#include <fstream>



/***
 * @brief class representing a word
 * @param data -> string containing the actual word
 * @param count -> size_t representing how much copies of the word exist
 */
struct Word{
    std::string data;
    size_t count;

    ///Default constructor
    Word(std::string Data, size_t Count){
        this->data = Data;
        this->count = Count;
    }
};



///
/// Represents a multiset of words
///
/// If you need to see how it is intended to be used,
/// check out the corresponding unit tests
///
/// Implement all methods of this class
///
///@param hashTable -> vector of pointers to forward lists that contain pointers to words
///                    representing the hashtable of words
///@param size -> the number of all words in the vector, including copies
///@param uniqueSize -> the number of all words in the vector that appear once
///@param arrLen -> the length of the vector (saved because the arrLen scales depending on the file size)
///@param valueIndexes -> public vector of size_t numbers that contains only the indexes of the hashTable array that have at least one Word* in them
/// 
class WordsMultiset {
public:
    /// Adds times occurences of word to the container
    ///
    /// For example, add("abc") adds the word "abc" once,
    /// while add("abc", 4) adds 4 occurrances.
    void add(const std::string& word, size_t times = 1);

    /// Checks whether word is contained in the container
    bool contains(const std::string& word) const;

    /// Number of occurrances of word
    size_t countOf(const std::string& word) const;

    /// Number of unique words in the container
    size_t countOfUniqueWords() const;

    /// Returns a multiset of all words in the container
    std::multiset<std::string> words() const;

    // You can add additional members if you need to
private:
    std::vector<std::forward_list<Word*>*> hashTable;  //will scale depending on the given istream
    size_t size;
    size_t uniqueSize;
    size_t arrLen;

public:
    ///public vector of size_t numbers that contains only the indexes of the hashTable array that have at least one Word* in them
    std::vector<size_t> valueIndexes;
    ///size getter
    ///@returns @param size
    size_t getSize();

    ///@brief constructor that gets as an argument input stream and creates hash table of Word's from it
    ///@param in -> input stream to read and create hash table from
    WordsMultiset(std::istream& in);

    ///@brief default constructor that sets everything to 0
    WordsMultiset();

    ///@brief destructor, deletes all LL in the vector and then clears the vector
    ~WordsMultiset();

    ///Copy c-tor
    WordsMultiset(const WordsMultiset& rhs);

    ///overriden operator= used for tests only
    WordsMultiset &operator= (const WordsMultiset& rhs);

    ///swap function that swaps the hashTables and sizes of two WordMultisets
    WordsMultiset& swap(WordsMultiset& rhs);

    ///size of the vector getter
    size_t getLen();

    ///@brief function that extracts all the words from the hashTable at a given index
    ///@param index -> index of the vector to be extracted
    ///@returns vector of Word* containing the words in the LL at the given index of the vector
    std::vector<Word*> getAllWords(size_t index);

    ///@brief removes the given word, as much times as we say (default is only 1 time)
    ///@param word -> word to be removed from the hashTable
    ///@param times -> how much copies of the word to remove
    ///@throws std::runtime_error if @param times is greater than the copies of the word
    void remove(const std::string& word, size_t times = 1);

};

///
/// Results of the comparison of two streams of words
/// DO NOT modify this class
/// If you need to see how it is intended to be used,
/// check out the corresponding unit tests
///
class ComparisonReport {
public:
    /// A multiset of all words that exist in both streams
    WordsMultiset commonWords;

    /// Multisets of words unique to the two streams
    /// The first element of the array contains the words that are unique
    /// to the first stream (a) and the second one -- to the second stream (b)
    WordsMultiset uniqueWords[2];
};

/// 
/// Can be used to compare two streams of words
///
class Comparator {
public:
    ComparisonReport compare(std::istream& a, std::istream& b);

    // You can add additional members if you need to
};

#include "WordsMultiset.inl"
#include "Comparator.inl"