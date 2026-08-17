//
// Created by socks on 8/16/26.
//

#ifndef MYGAME_RANDOMSTUFF_H
#define MYGAME_RANDOMSTUFF_H
#include <random>

float getRandomFloat(std::ranlux24_base &rng, float min, float max);

int getRandomInt(std::ranlux24_base &rng, int min, int max);

bool getRandomChance(std::ranlux24_base &rng, float chance);

#endif //MYGAME_RANDOMSTUFF_H