#include "ext.h"

#include "airfx.hpp"
#include "subtlety/purestwarm.hpp"

using TWrapped = airwindohhs::purestwarm::PurestWarm<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestwarm~", airwindohhs::purestwarm::k_long_description.data());
}
