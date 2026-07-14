#include "ext.h"

#include "airfx.hpp"
#include "effects/aura.hpp"

using TWrapped = airwindohhs::aura::Aura<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.aura~", airwindohhs::aura::k_long_description.data());
}
