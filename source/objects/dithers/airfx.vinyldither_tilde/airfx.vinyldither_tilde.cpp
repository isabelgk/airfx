#include "ext.h"

#include "airfx.hpp"
#include "dithers/vinyldither.hpp"

using TWrapped = airwindohhs::vinyldither::VinylDither<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.vinyldither~", airwindohhs::vinyldither::k_long_description.data());
}
