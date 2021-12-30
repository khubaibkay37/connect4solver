#include "TranspositionTable.hpp"

unsigned int TranspositionTable::index(uint64_t key) const
{
  return key % T.size();
}

TranspositionTable::TranspositionTable(unsigned int size) : T(size)
{
  assert(size > 0);
}

void TranspositionTable::reset()
{ // fill everything with 0, because 0 value means missing data
  memset(&T[0], 0, T.size() * sizeof(Entry));
}

/**
   * Store a value for a given key
   * @param key: 56-bit key
   * @param value: non-null 8-bit value. null (0) value are used to encode missing data.
   */
void TranspositionTable::put(uint64_t key, uint8_t val)
{
  assert(key < (1LL << 56));
  unsigned int i = index(key); // compute the index position
  T[i].key = key;              // and overide any existing value.
  T[i].val = val;
}

/** 
   * Get the value of a key
   * @param key
   * @return 8-bit value associated with the key if present, 0 otherwise.
   */
uint8_t TranspositionTable::get(uint64_t key) const
{
  assert(key < (1LL << 56));
  unsigned int i = index(key); // compute the index position
  if (T[i].key == key)
    return T[i].val; // and return value if key matches
  else
    return 0; // or 0 if missing entry
}
