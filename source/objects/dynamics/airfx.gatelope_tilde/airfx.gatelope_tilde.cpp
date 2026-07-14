#include "ext.h"

#include "airfx.hpp"
#include "dynamics/gatelope.hpp"

using TWrapped = airwindohhs::gatelope::Gatelope<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.gatelope~", airwindohhs::gatelope::k_long_description.data());
}
