#include "ext.h"

#include "airfx.hpp"
#include "subtlety/mastering2.hpp"

using TWrapped = airwindohhs::mastering2::Mastering2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.mastering2~", airwindohhs::mastering2::k_long_description.data());
}
