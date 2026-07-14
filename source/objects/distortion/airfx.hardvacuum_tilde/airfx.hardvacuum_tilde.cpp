#include "ext.h"

#include "airfx.hpp"
#include "distortion/hardvacuum.hpp"

using TWrapped = airwindohhs::hardvacuum::HardVacuum<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hardvacuum~", airwindohhs::hardvacuum::k_long_description.data());
}
