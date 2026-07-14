#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/derez3.hpp"

using TWrapped = airwindohhs::derez3::DeRez3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.derez3~", airwindohhs::derez3::k_long_description.data());
}
