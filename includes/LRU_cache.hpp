//
// Created by Shivam Verma on 24/10/24.
//

#pragma once
#include <list>

template<typename KeyType, typename ValueType>
class LRUCache {
public:
    explicit LRUCache(int capacity) : mCapacity(capacity) {}

    ValueType get(const KeyType& key) {
        if (mKeyToList.contains(key)) {
            // moved it to front of list (the iterator stays valid, hence don't update map)
            mCache.splice(mKeyToList.begin(), mCache, mKeyToList[key]);
            return mKeyToList[key]->second;
        }
        return ValueType();
    }

    void put(const KeyType& key, const ValueType& value) {
        if (mKeyToList.contains(key)) {
            mKeyToList[key]->second = value;
            mCache.splice(mKeyToList.begin(), mCache, mKeyToList[key]);
        } else {
            if (mKeyToList.size() == mCapacity) {
                KeyType KeyLeastRecentlyUsed = mCache.back().first;
                mKeyToList.erase(KeyLeastRecentlyUsed);
                mCache.pop_back();
            }
            mCache.emplace_front(key, value); // adding to front of list
            mKeyToList[key] = mCache.begin();
        }
    }

private:
    using CacheType = std::list<std::pair<KeyType, ValueType>>;
    using Iterator = typename std::list<std::pair<KeyType, ValueType>>::iterator;
    int mCapacity;
    CacheType mCache;
    std::unordered_map<KeyType, Iterator> mKeyToList;
};
