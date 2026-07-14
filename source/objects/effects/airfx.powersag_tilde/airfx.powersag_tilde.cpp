#include "ext.h"

#include "airfx.hpp"
#include "effects/powersag.hpp"

using TWrapped = airwindohhs::powersag::PowerSag<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.powersag~", airwindohhs::powersag::k_long_description.data());
}
