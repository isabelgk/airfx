#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/tapebias.hpp"

using TWrapped = airwindohhs::tapebias::TapeBias<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tapebias~", airwindohhs::tapebias::k_long_description.data());
}
