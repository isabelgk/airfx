#include "ext.h"

#include "airfx.hpp"
#include "filter/smootheq.hpp"

using TWrapped = airwindohhs::smootheq::SmoothEQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.smootheq~", airwindohhs::smootheq::k_long_description.data());
}
