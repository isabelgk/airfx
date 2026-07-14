#include "ext.h"

#include "airfx.hpp"
#include "dithers/paulwide.hpp"

using TWrapped = airwindohhs::paulwide::PaulWide<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.paulwide~", airwindohhs::paulwide::k_long_description.data());
}
