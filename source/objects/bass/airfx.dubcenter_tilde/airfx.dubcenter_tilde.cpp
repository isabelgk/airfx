#include "ext.h"

#include "airfx.hpp"
#include "bass/dubcenter.hpp"

using TWrapped = airwindohhs::dubcenter::DubCenter<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dubcenter~", airwindohhs::dubcenter::k_long_description.data());
}
