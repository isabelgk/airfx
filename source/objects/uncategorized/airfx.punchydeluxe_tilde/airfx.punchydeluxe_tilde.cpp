#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/punchydeluxe.hpp"

using TWrapped = airwindohhs::punchydeluxe::PunchyDeluxe<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.punchydeluxe~", airwindohhs::punchydeluxe::k_long_description.data());
}
