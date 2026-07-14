#include "ext.h"

#include "airfx.hpp"
#include "ambience/doublelay.hpp"

using TWrapped = airwindohhs::doublelay::Doublelay<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.doublelay~", airwindohhs::doublelay::k_long_description.data());
}
