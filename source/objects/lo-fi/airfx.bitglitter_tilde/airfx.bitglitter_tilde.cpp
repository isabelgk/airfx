#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/bitglitter.hpp"

using TWrapped = airwindohhs::bitglitter::BitGlitter<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bitglitter~", airwindohhs::bitglitter::k_long_description.data());
}
