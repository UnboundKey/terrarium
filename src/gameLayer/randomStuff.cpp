//
// Created by socks on 8/16/26.
//

#include "randomStuff.h"
float getRandomFloat(std::ranlux24_base &rng, float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(rng);
}

int getRandomInt(std::ranlux24_base &rng, int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(rng);
}

bool getRandomChance(std::ranlux24_base &rng, float chance) {
    float random = getRandomFloat(rng, 0.0, 1.0);
    return random <= chance;
}

