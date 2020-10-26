#ifndef FIGHT_H
#define FIGHT_H

#include "Monster.h"
#include "Utilities.h"

class Fight {
    public:
        static void attack(Monster &attacker, Monster &attackee);
        static Random r;
    private:
};

#endif