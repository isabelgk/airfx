#include "ext.h"

#include "airfx.hpp"
#include "utility/cansaw.hpp"

using TWrapped = airwindohhs::cansaw::CansAW<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cansaw~", airwindohhs::cansaw::k_long_description.data());
}
