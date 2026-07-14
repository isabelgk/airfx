#include "ext.h"

#include "airfx.hpp"
#include "subtlety/discontinuity.hpp"

using TWrapped = airwindohhs::discontinuity::Discontinuity<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.discontinuity~", airwindohhs::discontinuity::k_long_description.data());
}
