#include "ext.h"

#include "airfx.hpp"
#include "saturation/focus.hpp"

using TWrapped = airwindohhs::focus::Focus<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.focus~", airwindohhs::focus::k_long_description.data());
}
