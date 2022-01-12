#pragma once


void WordsMultiset::add(const std::string& word, size_t times){
    size_t index = std::hash<std::string>()(word) % arrLen;
    if(!hashTable[index]->empty()) {
        for (std::forward_list<Word*>::iterator iterator = hashTable[index]->begin(); iterator != hashTable[index]->end(); iterator++) {
            if (word == iterator.operator*()->data) {
                iterator.operator*()->count += times;
                size += times;
                return;
            }
        }
    }
    else{
        valueIndexes.push_back(index);
    }
    try {
        hashTable[index]->push_front(new Word(word, times));
        size += times;
        uniqueSize++;
    }
    catch(std::bad_alloc& e){
        std::cerr << e.what();
        delete hashTable[index]->front();
        hashTable[index]->pop_front();
        throw;
    }
}


void WordsMultiset::remove(const std::string& word, size_t times){
    size_t index = std::hash<std::string>()(word) % arrLen;
    if(!hashTable[index]->empty()) {
        for (std::forward_list<Word*>::iterator iterator = hashTable[index]->begin(); iterator != hashTable[index]->end(); iterator++) {
            if (word == iterator.operator*()->data) {
                if(times > iterator.operator*()->count){
                    throw std::runtime_error("You are trying to remove more words than there are in the table.");
                }
                iterator.operator*()->count -= times;
                size -= times;
                if(iterator.operator*()->count <= 0){
                    Word* tmp = *iterator;
                    hashTable[index]->remove(iterator.operator*());
                    uniqueSize--;
                    delete tmp;
                }
                return;
            }
        }
    }
    return;
}




bool WordsMultiset::contains(const std::string& word) const{
    size_t index = std::hash<std::string>()(word) % arrLen;
    for(auto iterator = hashTable[index]->begin(); iterator != hashTable[index]->end(); iterator++){
        if(word == iterator.operator*()->data){
            return true;
        }
    }
    return false;
}

//O(k)
size_t WordsMultiset::countOf(const std::string& word) const{
    size_t index = std::hash<std::string>()(word) % arrLen;
    for(auto iterator = hashTable[index]->begin(); iterator != hashTable[index]->end(); iterator++){
        if(word == iterator.operator*()->data){
            return iterator.operator*()->count;
        }
    }
    return 0;
}


size_t WordsMultiset::countOfUniqueWords() const{
    return this->uniqueSize;
}

std::multiset<std::string> WordsMultiset::words() const{
    std::multiset<std::string> result;
    int sz = valueIndexes.size();
    for(int i=0; i<sz; ++i){
        for(auto iterator = hashTable[valueIndexes[i]]->begin(); iterator != hashTable[valueIndexes[i]]->end(); iterator++){
            for(int j=0; j<iterator.operator*()->count; j++){
                result.insert(iterator.operator*()->data);
            }
        }
    }
    return result;
}

size_t WordsMultiset::getSize(){
    return this->size;
}

WordsMultiset::WordsMultiset(std::istream& in){
    //getting the count of the words by getting the count of all chars in the file and then dividing of 5 (average length of a word is 5)
    size_t sz = in.gcount()/5;

    size_t pow2to17 = 2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;

    //set to 2^17 if the count of the words in the stream is too high
    //that guarantees that I won't be using too much ram
    sz = pow2to17 < sz ? pow2to17 : sz;

    //if by some chance the size is 0 (after in.gcount()/5) make it so that the sz isn't 0
    if(sz == 0)
        sz = 2*2*2*2*2*2*2*2*2*2;

    try {
        this->hashTable.reserve(sz);
        for(int i=0; i<sz; ++i){
            std::forward_list<Word*>* list;
            list = new std::forward_list<Word*>;
            hashTable.push_back(list);
        }
        this->size = 0;
        this->uniqueSize = 0;
        this->arrLen = sz;
    }
    catch(std::length_error e){
        std::cerr << e.what();
        throw;
    }
    catch(...){
        std::cerr << "Memory error.";
        for (int i = 0; i < arrLen; ++i) {
            for(auto iterator = hashTable[i]->begin(); iterator != hashTable[i]->end(); iterator++){
                delete iterator.operator*();
            }
            delete hashTable[i];
        }
        throw;
    }
}


WordsMultiset::WordsMultiset(){
    this->size = 0;
    this->uniqueSize = 0;
    this->arrLen = 2*2*2*2*2*2*2*2*2*2;

    try {
        this->hashTable.reserve(arrLen);
        for(int i=0; i<arrLen; ++i){
            std::forward_list<Word*>* list;
            list = new std::forward_list<Word*>;
            hashTable.push_back(list);
        }
    }
    catch(std::length_error e){
        std::cerr << e.what();
        throw;
    }
    catch(...){
        std::cerr << "Memory error.";
        for (int i = 0; i < arrLen; ++i) {
            for(auto iterator = hashTable[i]->begin(); iterator != hashTable[i]->end(); iterator++){
                delete iterator.operator*();
            }
            delete hashTable[i];
        }
        throw;
    }
}

WordsMultiset::~WordsMultiset(){
    while(!hashTable.empty()){
        while(!hashTable.back()->empty()){
            delete hashTable.back()->front();
            hashTable.back()->pop_front();
        }
        delete hashTable.back();
        hashTable.pop_back();
    }
}

WordsMultiset::WordsMultiset(const WordsMultiset& rhs){
    this->hashTable = rhs.hashTable;
    this->size = rhs.size;
    this->uniqueSize = rhs.uniqueSize;
}


WordsMultiset& WordsMultiset::operator= (const WordsMultiset& rhs){
    if(this != &rhs){
        this->hashTable = rhs.hashTable;
        this->valueIndexes = rhs.valueIndexes;
        this->size = rhs.size;
        this->uniqueSize = rhs.uniqueSize;
    }
    return *this;
}

size_t WordsMultiset::getLen() {
    return this->arrLen;
}


//O(k) where k is the length of the LL in the vector at the given index
std::vector<Word*> WordsMultiset::getAllWords(size_t index){
    std::vector<Word*> result;
    for(auto iterator = this->hashTable[index]->begin(); iterator != this->hashTable[index]->end(); iterator++){
        result.push_back(new Word(iterator.operator*()->data, iterator.operator*()->count));
    }
    return result;
}

WordsMultiset& WordsMultiset::swap(WordsMultiset& rhs){
    std::vector<std::forward_list<Word*>*> tmp = hashTable;
    hashTable = rhs.hashTable;
    rhs.hashTable = tmp;

    std::vector<size_t> tmpVal = valueIndexes;
    valueIndexes = rhs.valueIndexes;
    rhs.valueIndexes = tmpVal;

    size_t tmpSz = size;
    size = rhs.size;
    rhs.size = tmpSz;

    tmpSz = uniqueSize;
    uniqueSize = rhs.uniqueSize;
    rhs.uniqueSize = tmpSz;

    tmpSz = arrLen;
    arrLen = rhs.arrLen;
    rhs.arrLen = tmpSz;

    return *this;
}