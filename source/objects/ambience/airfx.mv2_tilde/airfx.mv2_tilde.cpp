#include "ext.h"

#include "airfx.hpp"
#include "ambience/mv2.hpp"

using TWrapped = airwindohhs::mv2::MV2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.mv2~", airwindohhs::mv2::k_long_description.data());
}
