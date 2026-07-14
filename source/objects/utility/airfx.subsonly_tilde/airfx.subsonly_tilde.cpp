#include "ext.h"

#include "airfx.hpp"
#include "utility/subsonly.hpp"

using TWrapped = airwindohhs::subsonly::SubsOnly<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.subsonly~", airwindohhs::subsonly::k_long_description.data());
}
