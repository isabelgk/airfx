#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/punchyguitar.hpp"

using TWrapped = airwindohhs::punchyguitar::PunchyGuitar<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.punchyguitar~", airwindohhs::punchyguitar::k_long_description.data());
}
