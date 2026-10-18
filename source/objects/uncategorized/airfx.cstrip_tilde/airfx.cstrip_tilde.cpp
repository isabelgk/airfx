#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/cstrip.hpp"

using TWrapped = airwindohhs::cstrip::CStrip<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cstrip~", airwindohhs::cstrip::k_long_description.data());
}
