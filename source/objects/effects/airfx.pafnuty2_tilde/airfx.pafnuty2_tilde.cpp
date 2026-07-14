#include "ext.h"

#include "airfx.hpp"
#include "effects/pafnuty2.hpp"

using TWrapped = airwindohhs::pafnuty2::Pafnuty2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pafnuty2~", airwindohhs::pafnuty2::k_long_description.data());
}
