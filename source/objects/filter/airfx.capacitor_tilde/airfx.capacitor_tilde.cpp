#include "ext.h"

#include "airfx.hpp"
#include "filter/capacitor.hpp"

using TWrapped = airwindohhs::capacitor::Capacitor<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.capacitor~", airwindohhs::capacitor::k_long_description.data());
}
