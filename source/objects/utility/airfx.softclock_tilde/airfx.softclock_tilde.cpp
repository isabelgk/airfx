#include "ext.h"

#include "airfx.hpp"
#include "utility/softclock.hpp"

using TWrapped = airwindohhs::softclock::SoftClock<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.softclock~", airwindohhs::softclock::k_long_description.data());
}
