#include "ext.h"

#include "airfx.hpp"
#include "filter/bezeq3.hpp"

using TWrapped = airwindohhs::bezeq3::BezEQ3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bezeq3~", airwindohhs::bezeq3::k_long_description.data());
}
