#include "ext.h"

#include "airfx.hpp"
#include "subtlety/transdesk.hpp"

using TWrapped = airwindohhs::transdesk::TransDesk<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.transdesk~", airwindohhs::transdesk::k_long_description.data());
}
