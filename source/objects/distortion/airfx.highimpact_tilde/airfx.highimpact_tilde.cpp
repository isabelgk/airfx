#include "ext.h"

#include "airfx.hpp"
#include "distortion/highimpact.hpp"

using TWrapped = airwindohhs::highimpact::HighImpact<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.highimpact~", airwindohhs::highimpact::k_long_description.data());
}
