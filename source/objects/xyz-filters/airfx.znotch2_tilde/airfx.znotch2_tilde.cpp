#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/znotch2.hpp"

using TWrapped = airwindohhs::znotch2::ZNotch2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.znotch2~", airwindohhs::znotch2::k_long_description.data());
}
