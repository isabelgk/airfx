#include "ext.h"

#include "airfx.hpp"
#include "brightness/sinew.hpp"

using TWrapped = airwindohhs::sinew::Sinew<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.sinew~", airwindohhs::sinew::k_long_description.data());
}
