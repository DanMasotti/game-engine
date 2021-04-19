#ifndef RNG_H
#define RNG_H

#include <random>

class RNG
{
public:
    RNG();

    static std::default_random_engine s_generator;
    static std::uniform_real_distribution<float> s_distribution;

    float getRandomNumber() const;

};

#endif // RNG_H
