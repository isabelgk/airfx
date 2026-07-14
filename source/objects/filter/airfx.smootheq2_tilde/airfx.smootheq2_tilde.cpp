#include "ext.h"

#include "airfx.hpp"
#include "filter/smootheq2.hpp"

using TWrapped = airwindohhs::smootheq2::SmoothEQ2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.smootheq2~", airwindohhs::smootheq2::k_long_description.data());
}
