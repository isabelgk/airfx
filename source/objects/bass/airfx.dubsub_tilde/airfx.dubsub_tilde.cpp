#include "ext.h"

#include "airfx.hpp"
#include "bass/dubsub.hpp"

using TWrapped = airwindohhs::dubsub::DubSub<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dubsub~", airwindohhs::dubsub::k_long_description.data());
}
