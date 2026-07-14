#include "ext.h"

#include "airfx.hpp"
#include "subtlety/mastering.hpp"

using TWrapped = airwindohhs::mastering::Mastering<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.mastering~", airwindohhs::mastering::k_long_description.data());
}
