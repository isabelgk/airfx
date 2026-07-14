#include "ext.h"

#include "airfx.hpp"
#include "effects/galacticvibe.hpp"

using TWrapped = airwindohhs::galacticvibe::GalacticVibe<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.galacticvibe~", airwindohhs::galacticvibe::k_long_description.data());
}
