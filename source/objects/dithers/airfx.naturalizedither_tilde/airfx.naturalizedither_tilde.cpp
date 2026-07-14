#include "ext.h"

#include "airfx.hpp"
#include "dithers/naturalizedither.hpp"

using TWrapped = airwindohhs::naturalizedither::NaturalizeDither<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.naturalizedither~", airwindohhs::naturalizedither::k_long_description.data());
}
