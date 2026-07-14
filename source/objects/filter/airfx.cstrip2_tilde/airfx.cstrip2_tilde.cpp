#include "ext.h"

#include "airfx.hpp"
#include "filter/cstrip2.hpp"

using TWrapped = airwindohhs::cstrip2::CStrip2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cstrip2~", airwindohhs::cstrip2::k_long_description.data());
}
