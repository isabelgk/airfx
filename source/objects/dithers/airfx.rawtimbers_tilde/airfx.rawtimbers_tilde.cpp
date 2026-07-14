#include "ext.h"

#include "airfx.hpp"
#include "dithers/rawtimbers.hpp"

using TWrapped = airwindohhs::rawtimbers::RawTimbers<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.rawtimbers~", airwindohhs::rawtimbers::k_long_description.data());
}
