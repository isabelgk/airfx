#include "ext.h"

#include "airfx.hpp"
#include "reverb/kwoodroom.hpp"

using TWrapped = airwindohhs::kwoodroom::kWoodRoom<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kwoodroom~", airwindohhs::kwoodroom::k_long_description.data());
}
