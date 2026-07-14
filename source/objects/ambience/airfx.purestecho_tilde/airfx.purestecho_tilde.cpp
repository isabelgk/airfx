#include "ext.h"

#include "airfx.hpp"
#include "ambience/purestecho.hpp"

using TWrapped = airwindohhs::purestecho::PurestEcho<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestecho~", airwindohhs::purestecho::k_long_description.data());
}
