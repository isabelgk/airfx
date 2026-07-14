#include "ext.h"

#include "airfx.hpp"
#include "effects/nikola.hpp"

using TWrapped = airwindohhs::nikola::Nikola<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.nikola~", airwindohhs::nikola::k_long_description.data());
}
