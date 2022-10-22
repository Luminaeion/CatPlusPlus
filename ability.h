#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

enum class abilityTarget { SELF, ENEMY, ALLY };
enum class abilityScaler { NONE, STR, AGI, INT };

struct Ability {
    Ability(string name, uint32_t cost, uint32_t cd, abilityTarget t, uint32_t hpe, abilityScaler s) : Name(name), Cost(cost), Cooldown(cd), Target(t), hpEffect(hpe), Scaler(s) {}
    string Name = "unnamed";
    uint32_t Cost = 0; // assume mp if there is cost
    uint32_t Cooldown = 1; // # of rounds to wait until it can be used again
    abilityTarget Target = abilityTarget::SELF;
    uint32_t hpEffect = 1;
    abilityScaler Scaler = abilityScaler::NONE;
};