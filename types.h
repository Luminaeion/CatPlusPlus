#include <cstdint>

// unsigned int stattype breaks debuffs cuz values can't go below 0
typedef std::int16_t stattype; // stats & buffs
typedef std::uint32_t welltype; // pointwell
typedef std::uint16_t dmgtype; // weapons
typedef std::uint16_t itemCount; // stackable & consumable items

typedef std::uint64_t exptype; // playercharacter
typedef std::uint16_t lvltype; // playercharacter