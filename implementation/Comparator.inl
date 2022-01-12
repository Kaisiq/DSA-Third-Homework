#pragma once

size_t max(size_t a, size_t b){
    return a>b ? a : b;
}

size_t min(size_t a, size_t b){
    return a>b ? b : a;
}

//O(8*k) ~ O(N)
ComparisonReport Comparator::compare(std::istream &a, std::istream &b) {
    ComparisonReport result;

//    WordsMultiset bothStreams[2];
//    bothStreams[0].swap(WordsMultiset(a));
//    bothStreams[1] = WordsMultiset(b);

    std::string word;
    while (a >> word){
        //O(k) where k is the length of the LL at the index we are adding in
        result.uniqueWords[0].add(word);
    }
    while (b >> word){
        //O(k) where k is the length of the LL at the index we are adding in
        result.uniqueWords[1].add(word);
    }

//    WordsMultiset c(a.gcount() > b.gcount() ? a : b);

    int countTo = min(result.uniqueWords[0].valueIndexes.size(), result.uniqueWords[1].valueIndexes.size());
    bool thisStream = countTo == result.uniqueWords[0].valueIndexes.size() ? 0 : 1;
    bool otherStream = !thisStream;

    for(int i=0; i<countTo; ++i){
        std::vector<Word*> allWords;
        //O(k)
        allWords = result.uniqueWords[thisStream].getAllWords(result.uniqueWords[thisStream].valueIndexes[i]);
        size_t allWordsSz = allWords.size();
        //O(k)
        for(int j=0; j<allWordsSz; ++j){
            //O(k)
            size_t inThis = result.uniqueWords[thisStream].countOf(allWords[j]->data);
            //O(k)
            size_t inOther = result.uniqueWords[otherStream].countOf(allWords[j]->data);
            if(inOther){
                size_t minToRemove = min(inThis,inOther);
                result.commonWords.add(allWords[j]->data, minToRemove);
                try {
                    //O(k)
                    result.uniqueWords[thisStream].remove(allWords[j]->data, minToRemove);
                    //O(k)
                    result.uniqueWords[otherStream].remove(allWords[j]->data, minToRemove);
                }
                catch(std::runtime_error& e){
                    std::cerr << e.what();
                    throw;
                }
            }
        }
        while(!allWords.empty()){
            delete allWords.back();
            allWords.pop_back();
        }
    }




//    ComparisonReport result;
//    result.uniqueWords[0].swap(bothStreams[0]);
//    result.uniqueWords[1].swap(bothStreams[1]);
//    result.commonWords.swap(c);
    return result;
}