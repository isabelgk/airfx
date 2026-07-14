#include "ext.h"

#include "airfx.hpp"
#include "dithers/ditherfloat.hpp"

using TWrapped = airwindohhs::ditherfloat::DitherFloat<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ditherfloat~", airwindohhs::ditherfloat::k_long_description.data());
}
