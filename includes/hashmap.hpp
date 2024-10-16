//
// Created by Shivam Verma on 15/10/24.
//

#pragma once
#include <cassert>
#include <list>
#include <vector>

template<typename KeyType, typename ValueType>
class HashMap {
public:
    explicit HashMap(const int capacity = 10) : mSize(0), mCapacity(capacity), mMaxLoad(0.75) {
        assert(mCapacity != 0);
        mTable.resize(mCapacity);
    }

    void insert(const KeyType& key, const ValueType& val) {
        const int index = HashFunction(key);
        for (auto& [k, v]: mTable[index]) {
            if (k == key) {
                v = val;
                return;
            }
        }
        mTable[index].emplace_back(key, val);
        mSize++;
        CheckLoadFactor();
    }

    ValueType get(const KeyType& key) const {
        const int index = HashFunction(key);
        for (const auto& [k, v]: mTable[index]) {
            if (k == key) {
                return v;
            }
        }
        throw std::runtime_error("Key does not exist");
    }

    bool containsKey(const KeyType& key) const {
        const int index = HashFunction(key);
        for (const auto& [k, v]: mTable[index]) {
            if (k == key) {
                return true;
            }
        }
        return false;
    }

    void remove(const KeyType& key) {
        const int index = HashFunction(key);
        for (auto it = mTable[index].begin(); it != mTable[index].end(); it++) {
            if (it->first == key) {
                mTable[index].erase(it);
                mSize--;
                return;
            }
        }
    }

    int getSize() const {
        return mSize;
    }

    bool isEmpty() const {
        return mSize == 0;
    }

private:
    std::vector<std::list<std::pair<KeyType, ValueType>>> mTable;
    int mSize;
    int mCapacity;
    float mMaxLoad;

    int HashFunction(const KeyType& key) const {
        return (std::hash<KeyType>{}(key) % mCapacity);
    }
    void CheckLoadFactor() {
        float loadFactor = static_cast<float>(mSize) / mCapacity;
        if (loadFactor > mMaxLoad) {
            rehash();
        }
    }

    void rehash() {
        int oldCapacity = mCapacity;
        mCapacity *= 2;
        std::vector<std::list<std::pair<KeyType, ValueType>>> newTable(mCapacity);
        for (int idx = 0; idx < oldCapacity; idx++) {
            for (const auto& [k, v]: mTable[idx]) {
                int newIndex = HashFunction(k);
                newTable[newIndex].emplace_back(k, v);
            }
        }
        mTable = std::move(newTable);
    }
};
