#include "ext.h"

#include "airfx.hpp"
#include "utility/lrconvolve.hpp"

using TWrapped = airwindohhs::lrconvolve::LRConvolve<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.lrconvolve~", airwindohhs::lrconvolve::k_long_description.data());
}
