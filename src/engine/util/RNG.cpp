#include "RNG.h"

std::default_random_engine  RNG::s_generator;
std::uniform_real_distribution<float> RNG::s_distribution = std::uniform_real_distribution<float>(0.f, 1.f);

RNG::RNG()
{

}

float RNG::getRandomNumber() const {
    return s_distribution(s_generator);
}
