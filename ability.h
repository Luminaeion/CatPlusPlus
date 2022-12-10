#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

enum class abilityTarget { SELF, ENEMY, ALLY };
enum class abilityScaler { NONE, STR, AGI, INT };

struct Ability {

  Ability(
  string name = "unnamed",
  uint32_t hpe = 1u,
  Buff* b = nullptr,
  uint32_t cost = 0u,
  uint32_t cd = 1u,
  abilityTarget t = abilityTarget::SELF,
  abilityScaler s = abilityScaler::NONE): Name(name), HpEffect(hpe), givenBuff(b), Cost(cost), Cooldown(cd), Target(t), Scaler(s) {
  }

  std::string Name;
  uint32_t HpEffect;
  Buff* givenBuff;
  uint32_t Cost;      // assume mp if there is a cost
  uint32_t Cooldown;  // number of rounds you have to wait before using it again
  abilityTarget Target;
  abilityScaler Scaler;

  ~Ability() {
    if (givenBuff) {
        delete givenBuff;
        givenBuff = nullptr;
    }
  }
};