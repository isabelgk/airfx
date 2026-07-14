#include "ext.h"

#include "airfx.hpp"
#include "ambience/mv.hpp"

using TWrapped = airwindohhs::mv::MV<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.mv~", airwindohhs::mv::k_long_description.data());
}
