#include "ext.h"

#include "airfx.hpp"
#include "effects/disintegrate.hpp"

using TWrapped = airwindohhs::disintegrate::Disintegrate<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.disintegrate~", airwindohhs::disintegrate::k_long_description.data());
}
