#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/spiral3.hpp"

using TWrapped = airwindohhs::spiral3::Spiral3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.spiral3~", airwindohhs::spiral3::k_long_description.data());
}
