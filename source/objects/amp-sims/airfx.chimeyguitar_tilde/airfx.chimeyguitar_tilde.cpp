#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/chimeyguitar.hpp"

using TWrapped = airwindohhs::chimeyguitar::ChimeyGuitar<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.chimeyguitar~", airwindohhs::chimeyguitar::k_long_description.data());
}
