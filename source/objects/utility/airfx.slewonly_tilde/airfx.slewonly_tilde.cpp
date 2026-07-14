#include "ext.h"

#include "airfx.hpp"
#include "utility/slewonly.hpp"

using TWrapped = airwindohhs::slewonly::SlewOnly<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.slewonly~", airwindohhs::slewonly::k_long_description.data());
}
