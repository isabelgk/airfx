#include "ext.h"

#include "airfx.hpp"
#include "subtlety/purestwarm3.hpp"

using TWrapped = airwindohhs::purestwarm3::PurestWarm3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestwarm3~", airwindohhs::purestwarm3::k_long_description.data());
}
