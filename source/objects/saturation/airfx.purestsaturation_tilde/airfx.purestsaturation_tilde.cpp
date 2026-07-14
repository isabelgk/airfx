#include "ext.h"

#include "airfx.hpp"
#include "saturation/purestsaturation.hpp"

using TWrapped = airwindohhs::purestsaturation::PurestSaturation<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestsaturation~", airwindohhs::purestsaturation::k_long_description.data());
}
