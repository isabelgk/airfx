#include "ext.h"

#include "airfx.hpp"
#include "saturation/longhand.hpp"

using TWrapped = airwindohhs::longhand::Longhand<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.longhand~", airwindohhs::longhand::k_long_description.data());
}
