#include "ext.h"

#include "airfx.hpp"
#include "filter/toneslant.hpp"

using TWrapped = airwindohhs::toneslant::ToneSlant<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.toneslant~", airwindohhs::toneslant::k_long_description.data());
}
