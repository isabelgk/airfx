#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/wolfbot.hpp"

using TWrapped = airwindohhs::wolfbot::Wolfbot<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.wolfbot~", airwindohhs::wolfbot::k_long_description.data());
}
