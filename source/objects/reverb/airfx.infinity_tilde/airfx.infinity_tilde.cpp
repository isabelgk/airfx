#include "ext.h"

#include "airfx.hpp"
#include "reverb/infinity.hpp"

using TWrapped = airwindohhs::infinity::Infinity<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.infinity~", airwindohhs::infinity::k_long_description.data());
}
