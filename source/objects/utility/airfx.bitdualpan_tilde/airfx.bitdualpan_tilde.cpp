#include "ext.h"

#include "airfx.hpp"
#include "utility/bitdualpan.hpp"

using TWrapped = airwindohhs::bitdualpan::BitDualPan<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bitdualpan~", airwindohhs::bitdualpan::k_long_description.data());
}
