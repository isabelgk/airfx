#include "ext.h"

#include "airfx.hpp"
#include "filter/dattorro.hpp"

using TWrapped = airwindohhs::dattorro::Dattorro<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dattorro~", airwindohhs::dattorro::k_long_description.data());
}
