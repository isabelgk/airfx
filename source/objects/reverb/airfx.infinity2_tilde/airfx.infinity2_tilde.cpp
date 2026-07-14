#include "ext.h"

#include "airfx.hpp"
#include "reverb/infinity2.hpp"

using TWrapped = airwindohhs::infinity2::Infinity2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.infinity2~", airwindohhs::infinity2::k_long_description.data());
}
