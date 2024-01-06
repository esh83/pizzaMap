#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <functional>
#include "schemma.h"

template <typename T>
class HashTable
{

    public:

        typedef std::function<unsigned int(const std::string&)> HashFunction;

        static const  unsigned int INITIAL_BUCKET_COUNT = 10;


    public:
        HashTable();
        HashTable(HashFunction hasher);
        HashTable(const HashTable& hm);
        ~HashTable();
        HashTable& operator=(const HashTable& hm);
        void add(const std::string& key, const T& value);
        void remove(const std::string& key);
        bool contains(const std::string& key) const;
        T value(const std::string& key) const;
        unsigned int size() const;
        unsigned int bucketCount() const;
        double loadFactor() const;
        unsigned int maxBucketSize() const;
        void printSelf();

    private:
        struct Node
        {
            std::string key;
            T value;
            Node* next;
        };

        void copyBuckets(Node** source, Node** destination, unsigned int size);
        void rebuildMap(Node** oldBuckets, unsigned int oldNumBuckets);
        HashFunction hasher;
        Node** buckets;
        unsigned int numBuckets;
        unsigned int numItems;


    };

#endif // HASHTABLE_H
