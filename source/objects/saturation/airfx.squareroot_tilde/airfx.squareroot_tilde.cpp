#include "ext.h"

#include "airfx.hpp"
#include "saturation/squareroot.hpp"

using TWrapped = airwindohhs::squareroot::SquareRoot<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.squareroot~", airwindohhs::squareroot::k_long_description.data());
}
