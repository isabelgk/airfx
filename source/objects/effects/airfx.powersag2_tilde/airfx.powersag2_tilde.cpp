#include "ext.h"

#include "airfx.hpp"
#include "effects/powersag2.hpp"

using TWrapped = airwindohhs::powersag2::PowerSag2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.powersag2~", airwindohhs::powersag2::k_long_description.data());
}
