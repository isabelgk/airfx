#include "ext.h"

#include "airfx.hpp"
#include "clipping/cliponly.hpp"

using TWrapped = airwindohhs::cliponly::ClipOnly<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cliponly~", airwindohhs::cliponly::k_long_description.data());
}
