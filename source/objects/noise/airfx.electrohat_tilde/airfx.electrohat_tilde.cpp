#include "ext.h"

#include "airfx.hpp"
#include "noise/electrohat.hpp"

using TWrapped = airwindohhs::electrohat::ElectroHat<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.electrohat~", airwindohhs::electrohat::k_long_description.data());
}
