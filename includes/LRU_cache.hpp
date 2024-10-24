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
        if (mCacheMap.find(key) != mCacheMap.end()) {
            // moved it to front of list (the iterator stays valid, hence don't update map)
            mCacheList.splice(mCacheMap.begin(), mCacheList, mCacheMap[key]);
            return mCacheMap[key]->second;
        }
        return ValueType();
    }

    void put(const KeyType& key, const ValueType& value) {
        if (mCacheMap.find(key) = mCacheMap.end()) {
            mCacheMap[key]->second = value;
            mCacheList.splice(mCacheMap.begin(), mCacheList, mCacheMap[key]);
        } else {
            if (mCacheMap.size() == mCapacity) {
                KeyType KeyLeastRecentlyUsed = mCacheList.back().first;
                mCacheMap.erase(KeyLeastRecentlyUsed);
                mCacheList.pop_back();
            }
            mCacheList.emplace_front(key, value); // adding to front of list
            mCacheMap[key] = mCacheList.begin();
        }
    }

private:
    using CacheType = std::list<std::pair<KeyType, ValueType>>;
    using Iterator = typename std::list<std::pair<KeyType, ValueType>>::iterator;
    int mCapacity;
    CacheType mCacheList;
    std::unordered_map<KeyType, Iterator> mCacheMap;
};
