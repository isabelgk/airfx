#include "ext.h"

#include "airfx.hpp"
#include "filter/smootheq3.hpp"

using TWrapped = airwindohhs::smootheq3::SmoothEQ3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.smootheq3~", airwindohhs::smootheq3::k_long_description.data());
}
