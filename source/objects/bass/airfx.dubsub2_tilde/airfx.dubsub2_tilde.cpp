#include "ext.h"

#include "airfx.hpp"
#include "bass/dubsub2.hpp"

using TWrapped = airwindohhs::dubsub2::DubSub2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dubsub2~", airwindohhs::dubsub2::k_long_description.data());
}
