#include "ext.h"

#include "airfx.hpp"
#include "filter/tapefat.hpp"

using TWrapped = airwindohhs::tapefat::TapeFat<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tapefat~", airwindohhs::tapefat::k_long_description.data());
}
