#include "ext.h"

#include "airfx.hpp"
#include "effects/exciter.hpp"

using TWrapped = airwindohhs::exciter::Exciter<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.exciter~", airwindohhs::exciter::k_long_description.data());
}
