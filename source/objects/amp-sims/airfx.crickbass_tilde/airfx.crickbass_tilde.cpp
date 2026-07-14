#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/crickbass.hpp"

using TWrapped = airwindohhs::crickbass::CrickBass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.crickbass~", airwindohhs::crickbass::k_long_description.data());
}
