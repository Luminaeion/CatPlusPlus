#include <iostream>
#include <cstdint>
#include <string>

enum class abilityTarget { SELF, ENEMY, ALLY };
enum class abilityScaler { NONE, STR, AGI, INT };

class Ability {
public:
Ability (
string name = "unnamed",
uint32_t hpe = 1u,
Buff* b = nullptr,
uint32_t cost = 0u,
uint32_t cd = 1u,
uint32_t rcd = 0u,
abilityTarget t = abilityTarget::SELF,
abilityScaler s = abilityScaler::NONE): Name(name), HpEffect(hpe), givenBuff(b), Cost(cost), Cooldown(cd), remainingCooldown(rcd), Target(t), Scaler(s) {}

~Ability() {
  if (givenBuff) {
      delete givenBuff;
      givenBuff = nullptr;
  }
}

const string getName() const noexcept { return Name; }
const uint32_t getCooldown() const noexcept { return Cooldown; }
const uint32_t getHPEffect() const noexcept { return HpEffect; }
const Buff* getBuff() const noexcept { return givenBuff; }
const uint32_t getCost() const noexcept { return Cost; }
const abilityTarget getTarget() const noexcept { return Target; }
const abilityScaler getScaler() const noexcept { return Scaler; }

private:
std::string Name;
uint32_t HpEffect;
Buff* givenBuff;
uint32_t Cost;      // assume mp if there is a cost
uint32_t Cooldown;  // # of rounds to wait till ability is available
uint32_t remainingCooldown;
abilityTarget Target;
abilityScaler Scaler;
};