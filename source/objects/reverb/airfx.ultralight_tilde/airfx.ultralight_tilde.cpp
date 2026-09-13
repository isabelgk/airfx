#include "ext.h"

#include "airfx.hpp"
#include "reverb/ultralight.hpp"

using TWrapped = airwindohhs::ultralight::Ultralight<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ultralight~", airwindohhs::ultralight::k_long_description.data());
}
