#include "ext.h"

#include "airfx.hpp"
#include "subtlety/sweeten.hpp"

using TWrapped = airwindohhs::sweeten::Sweeten<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.sweeten~", airwindohhs::sweeten::k_long_description.data());
}
