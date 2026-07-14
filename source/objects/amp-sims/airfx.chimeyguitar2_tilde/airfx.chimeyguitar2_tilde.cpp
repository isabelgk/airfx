#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/chimeyguitar2.hpp"

using TWrapped = airwindohhs::chimeyguitar2::ChimeyGuitar2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.chimeyguitar2~", airwindohhs::chimeyguitar2::k_long_description.data());
}
