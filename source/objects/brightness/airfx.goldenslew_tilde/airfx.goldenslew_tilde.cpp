#include "ext.h"

#include "airfx.hpp"
#include "brightness/goldenslew.hpp"

using TWrapped = airwindohhs::goldenslew::GoldenSlew<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.goldenslew~", airwindohhs::goldenslew::k_long_description.data());
}
