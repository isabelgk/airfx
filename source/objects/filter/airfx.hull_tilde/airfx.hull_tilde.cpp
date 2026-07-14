#include "ext.h"

#include "airfx.hpp"
#include "filter/hull.hpp"

using TWrapped = airwindohhs::hull::Hull<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hull~", airwindohhs::hull::k_long_description.data());
}
