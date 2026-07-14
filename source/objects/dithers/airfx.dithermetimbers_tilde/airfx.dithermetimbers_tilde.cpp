#include "ext.h"

#include "airfx.hpp"
#include "dithers/dithermetimbers.hpp"

using TWrapped = airwindohhs::dithermetimbers::DitherMeTimbers<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dithermetimbers~", airwindohhs::dithermetimbers::k_long_description.data());
}
