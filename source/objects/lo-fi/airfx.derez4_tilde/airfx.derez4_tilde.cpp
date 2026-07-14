#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/derez4.hpp"

using TWrapped = airwindohhs::derez4::DeRez4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.derez4~", airwindohhs::derez4::k_long_description.data());
}
