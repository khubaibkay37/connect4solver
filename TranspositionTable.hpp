#include<vector>
#include<cstring>
#include<cassert>
#include <cstdint>


  struct Entry {
    uint64_t key: 56; // use 56-bit keys
    uint8_t val;      // use 8-bit values
  };                  // overall sizeof(Entry) = 8 bytes


/**
 * Transposition Table is a simple hash map with fixed storage size.
 * In case of collision we keep the last entry and overide the previous one.
 *
 * We use 56-bit keys and 8-bit non-null values
 */
class TranspositionTable {
  private:


  std::vector<Entry> T;

  unsigned int index(uint64_t key) const;
  public:

  TranspositionTable(unsigned int size);

  /*
   * Empty the Transition Table.
   */
  void reset();

  void put(uint64_t key, uint8_t val);

  /** 
   * Get the value of a key
   * @param key
   * @return 8-bit value associated with the key if present, 0 otherwise.
   */
  uint8_t get(uint64_t key) const;

};

