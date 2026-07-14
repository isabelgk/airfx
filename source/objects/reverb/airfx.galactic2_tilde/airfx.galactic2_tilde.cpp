#include "ext.h"

#include "airfx.hpp"
#include "reverb/galactic2.hpp"

using TWrapped = airwindohhs::galactic2::Galactic2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.galactic2~", airwindohhs::galactic2::k_long_description.data());
}
