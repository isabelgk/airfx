#include "ext.h"

#include "airfx.hpp"
#include "tone-color/neverland.hpp"

using TWrapped = airwindohhs::neverland::Neverland<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.neverland~", airwindohhs::neverland::k_long_description.data());
}
