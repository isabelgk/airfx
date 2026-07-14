#include "ext.h"

#include "airfx.hpp"
#include "effects/preponderant.hpp"

using TWrapped = airwindohhs::preponderant::Preponderant<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.preponderant~", airwindohhs::preponderant::k_long_description.data());
}
