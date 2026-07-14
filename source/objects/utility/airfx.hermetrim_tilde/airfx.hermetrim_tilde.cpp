#include "ext.h"

#include "airfx.hpp"
#include "utility/hermetrim.hpp"

using TWrapped = airwindohhs::hermetrim::HermeTrim<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hermetrim~", airwindohhs::hermetrim::k_long_description.data());
}
