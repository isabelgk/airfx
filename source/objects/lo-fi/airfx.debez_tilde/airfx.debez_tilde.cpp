#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/debez.hpp"

using TWrapped = airwindohhs::debez::DeBez<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.debez~", airwindohhs::debez::k_long_description.data());
}
