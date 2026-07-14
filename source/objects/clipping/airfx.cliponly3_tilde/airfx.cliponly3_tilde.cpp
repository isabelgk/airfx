#include "ext.h"

#include "airfx.hpp"
#include "clipping/cliponly3.hpp"

using TWrapped = airwindohhs::cliponly3::ClipOnly3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cliponly3~", airwindohhs::cliponly3::k_long_description.data());
}
