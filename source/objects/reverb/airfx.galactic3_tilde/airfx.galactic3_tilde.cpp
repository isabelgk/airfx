#include "ext.h"

#include "airfx.hpp"
#include "reverb/galactic3.hpp"

using TWrapped = airwindohhs::galactic3::Galactic3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.galactic3~", airwindohhs::galactic3::k_long_description.data());
}
