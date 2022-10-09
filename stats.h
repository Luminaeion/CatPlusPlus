#include <cstdint>

typedef std::uint16_t stattype;

class Stats {
    stattype Str; // Strength  // 0xFF
    //stattype Def; // Defence
public:
    Stats() { 
        Str = (stattype)1u;
    }
    explicit Stats(stattype s) { 
        Str = s;
    }
    stattype getStrength() { return Str; }
};

// Need to implement def into hp