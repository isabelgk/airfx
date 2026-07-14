#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/bassdrive.hpp"

using TWrapped = airwindohhs::bassdrive::BassDrive<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bassdrive~", airwindohhs::bassdrive::k_long_description.data());
}
