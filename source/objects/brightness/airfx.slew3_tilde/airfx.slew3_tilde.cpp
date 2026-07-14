#include "ext.h"

#include "airfx.hpp"
#include "brightness/slew3.hpp"

using TWrapped = airwindohhs::slew3::Slew3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.slew3~", airwindohhs::slew3::k_long_description.data());
}
