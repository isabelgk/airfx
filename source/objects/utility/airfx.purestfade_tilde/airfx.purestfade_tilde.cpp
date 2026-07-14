#include "ext.h"

#include "airfx.hpp"
#include "utility/purestfade.hpp"

using TWrapped = airwindohhs::purestfade::PurestFade<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestfade~", airwindohhs::purestfade::k_long_description.data());
}
