#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/derez2.hpp"

using TWrapped = airwindohhs::derez2::DeRez2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.derez2~", airwindohhs::derez2::k_long_description.data());
}
