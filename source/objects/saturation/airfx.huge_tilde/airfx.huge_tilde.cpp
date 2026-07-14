#include "ext.h"

#include "airfx.hpp"
#include "saturation/huge.hpp"

using TWrapped = airwindohhs::huge::Huge<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.huge~", airwindohhs::huge::k_long_description.data());
}
