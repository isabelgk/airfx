#include "ext.h"

#include "airfx.hpp"
#include "utility/purestdualpan.hpp"

using TWrapped = airwindohhs::purestdualpan::PurestDualPan<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestdualpan~", airwindohhs::purestdualpan::k_long_description.data());
}
