#include "ext.h"

#include "airfx.hpp"
#include "utility/softclock2.hpp"

using TWrapped = airwindohhs::softclock2::SoftClock2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.softclock2~", airwindohhs::softclock2::k_long_description.data());
}
