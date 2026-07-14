#include "ext.h"

#include "airfx.hpp"
#include "utility/softclock3.hpp"

using TWrapped = airwindohhs::softclock3::SoftClock3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.softclock3~", airwindohhs::softclock3::k_long_description.data());
}
