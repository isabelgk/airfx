#include "ext.h"

#include "airfx.hpp"
#include "bass/hermepass.hpp"

using TWrapped = airwindohhs::hermepass::Hermepass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hermepass~", airwindohhs::hermepass::k_long_description.data());
}
