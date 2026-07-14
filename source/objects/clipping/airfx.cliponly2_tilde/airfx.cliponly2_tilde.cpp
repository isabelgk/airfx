#include "ext.h"

#include "airfx.hpp"
#include "clipping/cliponly2.hpp"

using TWrapped = airwindohhs::cliponly2::ClipOnly2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cliponly2~", airwindohhs::cliponly2::k_long_description.data());
}
