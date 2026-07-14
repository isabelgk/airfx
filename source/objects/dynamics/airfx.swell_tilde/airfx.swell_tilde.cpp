#include "ext.h"

#include "airfx.hpp"
#include "dynamics/swell.hpp"

using TWrapped = airwindohhs::swell::Swell<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.swell~", airwindohhs::swell::k_long_description.data());
}
