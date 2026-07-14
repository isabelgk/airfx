#include "ext.h"

#include "airfx.hpp"
#include "subtlety/desk.hpp"

using TWrapped = airwindohhs::desk::Desk<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.desk~", airwindohhs::desk::k_long_description.data());
}
