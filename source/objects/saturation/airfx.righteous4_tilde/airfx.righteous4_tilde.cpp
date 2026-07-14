#include "ext.h"

#include "airfx.hpp"
#include "saturation/righteous4.hpp"

using TWrapped = airwindohhs::righteous4::Righteous4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.righteous4~", airwindohhs::righteous4::k_long_description.data());
}
