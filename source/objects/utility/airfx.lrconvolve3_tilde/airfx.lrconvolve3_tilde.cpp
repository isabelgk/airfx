#include "ext.h"

#include "airfx.hpp"
#include "utility/lrconvolve3.hpp"

using TWrapped = airwindohhs::lrconvolve3::LRConvolve3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.lrconvolve3~", airwindohhs::lrconvolve3::k_long_description.data());
}
