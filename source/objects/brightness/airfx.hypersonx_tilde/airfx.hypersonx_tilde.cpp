#include "ext.h"

#include "airfx.hpp"
#include "brightness/hypersonx.hpp"

using TWrapped = airwindohhs::hypersonx::HypersonX<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hypersonx~", airwindohhs::hypersonx::k_long_description.data());
}
