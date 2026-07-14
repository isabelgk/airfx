#include "ext.h"

#include "airfx.hpp"
#include "utility/everytrim.hpp"

using TWrapped = airwindohhs::everytrim::EveryTrim<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.everytrim~", airwindohhs::everytrim::k_long_description.data());
}
