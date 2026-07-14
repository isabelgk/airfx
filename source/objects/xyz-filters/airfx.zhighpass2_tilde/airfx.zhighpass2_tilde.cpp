#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zhighpass2.hpp"

using TWrapped = airwindohhs::zhighpass2::ZHighpass2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zhighpass2~", airwindohhs::zhighpass2::k_long_description.data());
}
