#pragma once
#include "interface.h"

size_t max(size_t a, size_t b){
    return a>b ? a : b;
}

size_t min(size_t a, size_t b){
    return a>b ? b : a;
}

//O(8*k) ~ O(N)
ComparisonReport Comparator::compare(std::istream &a, std::istream &b) {
    WordsMultiset bothStreams[2];
//    bothStreams[0].swap(WordsMultiset(a));
//    bothStreams[1] = WordsMultiset(b);

    std::string word;
    while (a >> word){
        //O(k) where k is the length of the LL at the index we are adding in
        bothStreams[0].add(word);
    }
    while (b >> word){
        //O(k) where k is the length of the LL at the index we are adding in
        bothStreams[1].add(word);
    }

    WordsMultiset c(a.gcount() > b.gcount() ? a : b);

    int countTo = min(bothStreams[0].valueIndexes.size(), bothStreams[1].valueIndexes.size());
    bool thisStream = countTo == bothStreams[0].valueIndexes.size() ? 0 : 1;
    bool otherStream = !thisStream;

    for(int i=0; i<countTo; ++i){
        std::vector<Word*> allWords;
        //O(k)
        allWords = bothStreams[thisStream].getAllWords(bothStreams[thisStream].valueIndexes[i]);
        size_t allWordsSz = allWords.size();
        //O(k)
        for(int j=0; j<allWordsSz; ++j){
            //O(k)
            size_t inThis = bothStreams[thisStream].countOf(allWords[j]->data);
            //O(k)
            size_t inOther = bothStreams[otherStream].countOf(allWords[j]->data);
            if(inOther){
                size_t minToRemove = min(inThis,inOther);
                c.add(allWords[j]->data, minToRemove);
                try {
                    //O(k)
                    bothStreams[thisStream].remove(allWords[j]->data, minToRemove);
                    //O(k)
                    bothStreams[otherStream].remove(allWords[j]->data, minToRemove);
                }
                catch(std::runtime_error& e){
                    std::cerr << e.what();
                    throw;
                }
            }
        }
    }




    ComparisonReport result;
    result.uniqueWords[0].swap(bothStreams[0]);
    result.uniqueWords[1].swap(bothStreams[1]);
    result.commonWords.swap(c);
    return result;
}