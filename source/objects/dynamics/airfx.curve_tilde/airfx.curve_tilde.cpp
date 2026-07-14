#include "ext.h"

#include "airfx.hpp"
#include "dynamics/curve.hpp"

using TWrapped = airwindohhs::curve::curve<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.curve~", airwindohhs::curve::k_long_description.data());
}
