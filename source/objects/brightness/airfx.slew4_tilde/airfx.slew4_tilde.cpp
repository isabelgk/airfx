#include "ext.h"

#include "airfx.hpp"
#include "brightness/slew4.hpp"

using TWrapped = airwindohhs::slew4::Slew4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.slew4~", airwindohhs::slew4::k_long_description.data());
}
