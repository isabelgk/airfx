#include "ext.h"

#include "airfx.hpp"
#include "subtlety/coils2.hpp"

using TWrapped = airwindohhs::coils2::Coils2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.coils2~", airwindohhs::coils2::k_long_description.data());
}
