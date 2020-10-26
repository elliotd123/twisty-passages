#include "Fight.h"

void Fight::attack(Monster &attacker, Monster &attackee) {
    int attack_power = r.dice_roll(1,attacker.attack);
    attackee.hp -= attack_power;
}