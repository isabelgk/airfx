#include "ext.h"

#include "airfx.hpp"
#include "dynamics/purestsquish.hpp"

using TWrapped = airwindohhs::purestsquish::PurestSquish<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestsquish~", airwindohhs::purestsquish::k_long_description.data());
}
