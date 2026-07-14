#include "ext.h"

#include "airfx.hpp"
#include "dynamics/logical4.hpp"

using TWrapped = airwindohhs::logical4::Logical4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.logical4~", airwindohhs::logical4::k_long_description.data());
}
