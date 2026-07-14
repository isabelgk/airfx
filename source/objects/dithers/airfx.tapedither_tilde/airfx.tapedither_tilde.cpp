#include "ext.h"

#include "airfx.hpp"
#include "dithers/tapedither.hpp"

using TWrapped = airwindohhs::tapedither::TapeDither<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tapedither~", airwindohhs::tapedither::k_long_description.data());
}
