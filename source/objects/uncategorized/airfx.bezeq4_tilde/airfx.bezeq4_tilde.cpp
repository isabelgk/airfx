#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/bezeq4.hpp"

using TWrapped = airwindohhs::bezeq4::BezEQ4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bezeq4~", airwindohhs::bezeq4::k_long_description.data());
}
