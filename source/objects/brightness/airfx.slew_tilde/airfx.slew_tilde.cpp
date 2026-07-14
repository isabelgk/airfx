#include "ext.h"

#include "airfx.hpp"
#include "brightness/slew.hpp"

using TWrapped = airwindohhs::slew::Slew<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.slew~", airwindohhs::slew::k_long_description.data());
}
