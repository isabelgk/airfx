#include "ext.h"

#include "airfx.hpp"
#include "subtlety/interstage.hpp"

using TWrapped = airwindohhs::interstage::Interstage<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.interstage~", airwindohhs::interstage::k_long_description.data());
}
