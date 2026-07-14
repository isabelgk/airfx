#include "ext.h"

#include "airfx.hpp"
#include "reverb/chamber2.hpp"

using TWrapped = airwindohhs::chamber2::Chamber2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.chamber2~", airwindohhs::chamber2::k_long_description.data());
}
