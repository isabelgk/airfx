#include "ext.h"

#include "airfx.hpp"
#include "brightness/slew2.hpp"

using TWrapped = airwindohhs::slew2::Slew2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.slew2~", airwindohhs::slew2::k_long_description.data());
}
