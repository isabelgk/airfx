#include "ext.h"

#include "airfx.hpp"
#include "reverb/kalienspaceship.hpp"

using TWrapped = airwindohhs::kalienspaceship::kAlienSpaceship<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kalienspaceship~", airwindohhs::kalienspaceship::k_long_description.data());
}
