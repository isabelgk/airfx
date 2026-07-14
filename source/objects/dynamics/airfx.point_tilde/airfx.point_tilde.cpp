#include "ext.h"

#include "airfx.hpp"
#include "dynamics/point.hpp"

using TWrapped = airwindohhs::point::Point<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.point~", airwindohhs::point::k_long_description.data());
}
