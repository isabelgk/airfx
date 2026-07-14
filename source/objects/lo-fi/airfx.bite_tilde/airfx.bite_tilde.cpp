#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/bite.hpp"

using TWrapped = airwindohhs::bite::Bite<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bite~", airwindohhs::bite::k_long_description.data());
}
