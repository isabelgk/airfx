#include "ext.h"

#include "airfx.hpp"
#include "filter/capacitor2.hpp"

using TWrapped = airwindohhs::capacitor2::Capacitor2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.capacitor2~", airwindohhs::capacitor2::k_long_description.data());
}
