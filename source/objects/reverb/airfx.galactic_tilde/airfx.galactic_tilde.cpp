#include "ext.h"

#include "airfx.hpp"
#include "reverb/galactic.hpp"

using TWrapped = airwindohhs::galactic::Galactic<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.galactic~", airwindohhs::galactic::k_long_description.data());
}
