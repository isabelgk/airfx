#include "ext.h"

#include "airfx.hpp"
#include "brightness/dehiss.hpp"

using TWrapped = airwindohhs::dehiss::DeHiss<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dehiss~", airwindohhs::dehiss::k_long_description.data());
}
