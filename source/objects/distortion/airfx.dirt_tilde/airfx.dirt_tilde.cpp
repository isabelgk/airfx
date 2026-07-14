#include "ext.h"

#include "airfx.hpp"
#include "distortion/dirt.hpp"

using TWrapped = airwindohhs::dirt::Dirt<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dirt~", airwindohhs::dirt::k_long_description.data());
}
