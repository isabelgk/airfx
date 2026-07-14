#include "ext.h"

#include "airfx.hpp"
#include "saturation/desk4.hpp"

using TWrapped = airwindohhs::desk4::Desk4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.desk4~", airwindohhs::desk4::k_long_description.data());
}
