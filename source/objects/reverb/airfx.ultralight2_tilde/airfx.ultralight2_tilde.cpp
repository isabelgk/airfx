#include "ext.h"

#include "airfx.hpp"
#include "reverb/ultralight2.hpp"

using TWrapped = airwindohhs::ultralight2::Ultralight2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ultralight2~", airwindohhs::ultralight2::k_long_description.data());
}
