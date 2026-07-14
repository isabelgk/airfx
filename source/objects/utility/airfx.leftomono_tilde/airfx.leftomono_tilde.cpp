#include "ext.h"

#include "airfx.hpp"
#include "utility/leftomono.hpp"

using TWrapped = airwindohhs::leftomono::LeftoMono<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.leftomono~", airwindohhs::leftomono::k_long_description.data());
}
