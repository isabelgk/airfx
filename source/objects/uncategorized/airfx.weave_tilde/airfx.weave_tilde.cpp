#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/weave.hpp"

using TWrapped = airwindohhs::weave::Weave<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.weave~", airwindohhs::weave::k_long_description.data());
}
