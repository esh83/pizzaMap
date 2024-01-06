#include "hashtable.h"
#include <iostream>
namespace {
unsigned int defaultHasher(const std::string &key) {
    unsigned int index = 0;

    for (int i = 0; i < key.length(); i++) {
        index += (int) key.at(i);
    }

    return index;
}
}

HashTable::HashTable()
    : hasher{defaultHasher},
    buckets{new Node*[INITIAL_BUCKET_COUNT]},
    numBuckets{INITIAL_BUCKET_COUNT}, numItems{0}
{

    for(int i = 0; i < numBuckets; i++){
        buckets[i] = nullptr;
    }

}

HashTable::HashTable(HashFunction hasher)
    : hasher{hasher},
    buckets{new Node*[INITIAL_BUCKET_COUNT]}, numBuckets{INITIAL_BUCKET_COUNT}
{

    for(int i = 0; i < numBuckets; i++){
        buckets[i] = nullptr;
    }
}

HashTable::HashTable(const HashTable& hm)
    : hasher{hm.hasher}, buckets{new Node*[hm.numBuckets]},
    numBuckets{hm.numBuckets}, numItems{hm.numItems}
{
    for(int i = 0; i < numBuckets; i++){
        buckets[i] = nullptr;
    }

    copyBuckets(hm.buckets, buckets, numBuckets);
}



HashTable::~HashTable() {
    for (unsigned int i = 0; i < numBuckets; i++) {
        Node *currentNode = buckets[i];

        while (currentNode != nullptr) {
            Node *toDelete = currentNode;
            currentNode = currentNode->next;

            delete toDelete;
        }

    }

    delete[] buckets;
}


HashTable& HashTable::operator=(const HashTable& hm){
    if (this != &hm){
        Node** newBuckets = new Node*[hm.numBuckets];

        copyBuckets(hm.buckets, newBuckets, hm.numBuckets);
        this->~HashTable();
        numBuckets = hm.numBuckets;
        numItems = hm.numItems;

        buckets = newBuckets;
    }

    return *this;
}


void HashTable::add(const std::string& key, const std::string& value){

    if((float)(numItems) / numBuckets > 0.8){
        unsigned int const oldNumBuckets = numBuckets;

        numBuckets = numBuckets*2 + 1;

        Node** newBucketList = new Node*[numBuckets];


        for(int i = 0; i < numBuckets; i++){
            newBucketList[i] = nullptr;
        }

        Node** oldBucketList = buckets;
        buckets = newBucketList;

        numItems = 0;
        //Build the new bucket list from the old
        rebuildMap(oldBucketList, oldNumBuckets);


        //Rebuild all buckets + rehash
        //Delete old bucket list

    }

    unsigned int bucketIndex = hasher(key) % numBuckets;

    Node* currentNode = buckets[bucketIndex];

    if(!contains(key)){

        Node* newNode = new Node{key, value, nullptr};

        if(currentNode == nullptr){
            buckets[bucketIndex] = newNode;

        }else{
            while(currentNode->next != nullptr){
                currentNode = currentNode->next;
            }
            currentNode->next = newNode;

        }

        //Increase numItems stored (size)
        numItems++;

    }else{
        //If the key already exists, override the value
        while(currentNode->key != key){
            currentNode = currentNode->next;
        }

        currentNode->value = value;
    }


}

void HashTable::remove(const std::string& key){
    unsigned int bucketIndex = hasher(key) % numBuckets;

    Node* currentNode = buckets[bucketIndex];
    Node* nextNode = currentNode->next;

    //If currentNode->next points to  value matching key, then delete it. and change
    //current Node's next to next next

    //If first node contains key
    if(currentNode->key == key){
        delete currentNode;

        buckets[bucketIndex] = nextNode;
        numItems--;


    }else{
        while (nextNode != nullptr) {
            if (nextNode->key == key) {
                //Delete this current value, point the node to the next
                currentNode->next = nextNode->next;
                delete nextNode;
                numItems--;
                break;

            }

            currentNode = currentNode->next;
            nextNode = currentNode->next;
        }
    }



}

bool HashTable::contains(const std::string& key) const{
    unsigned int bucketIndex = hasher(key) % numBuckets;

    Node* currentNode = buckets[bucketIndex];

    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return true;
        }
        currentNode = currentNode->next;
    }

    return false;
}

std::string HashTable::value(const std::string& key) const{
    unsigned int bucketIndex = hasher(key) % numBuckets;
    Node* currentNode = buckets[bucketIndex];

    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }

    return std::string("No value matching given key!");
}

unsigned int HashTable::size() const{
    return numItems;
}

unsigned int HashTable::bucketCount() const{
    return numBuckets;
}

unsigned int HashTable::maxBucketSize() const{
    // maxBucketSize() returns the number of key/value pairs stored in this
    // HashTable's largest bucket.
    unsigned int largestBucketSize = 0;

    for(unsigned int i = 0; i < numBuckets; i++){
        unsigned int currentBucketSize = 0;

        Node* currentNode = buckets[i];

        while(currentNode != nullptr){
            currentBucketSize++;
            currentNode = currentNode->next;
        }

        if(currentBucketSize > largestBucketSize){
            largestBucketSize = currentBucketSize;
        }
    }

    return largestBucketSize;

};

double HashTable::loadFactor() const{
    return (float) numItems / numBuckets;
}


void HashTable::copyBuckets(Node** source, Node** destination, unsigned int size){
    for(unsigned int i = 0; i < size; i++){
        Node* current = source[i];

        if(current != nullptr){
            Node* newNode = new Node;
            destination[i] = newNode;

            while(current != nullptr){
                newNode->key = current->key;
                newNode->value = current->value;
                newNode->next = new Node;

                current = current->next;
                newNode = newNode->next;

            }

            //Last new pointer in bucket
            newNode->next = nullptr;
        }

    }
}

void HashTable::rebuildMap(Node** oldBuckets, unsigned int oldNumBuckets) {
    for (unsigned int i = 0; i < oldNumBuckets; i++) {
        Node *currentNode = oldBuckets[i];

        while (currentNode != nullptr) {
            add(currentNode->key, currentNode->value);

            Node *toDelete = currentNode;
            currentNode = currentNode->next;

            delete toDelete;


        }

    }

    delete[] oldBuckets;

}



void HashTable::printSelf() {
    for(int i = 0; i < numBuckets; i++){
        Node *currentNode = buckets[i];
        std::cout << "Index: " << i << " ";

        while(currentNode != nullptr){
            std::cout << "-> (" << currentNode->key << ", " << currentNode->value << ")";
            currentNode = currentNode->next;
        }
        std::cout << std::endl;

    }
}
