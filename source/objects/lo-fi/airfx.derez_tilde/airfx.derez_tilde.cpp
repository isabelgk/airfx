#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/derez.hpp"

using TWrapped = airwindohhs::derez::DeRez<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.derez~", airwindohhs::derez::k_long_description.data());
}
