#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/deckwrecka.hpp"

using TWrapped = airwindohhs::deckwrecka::Deckwrecka<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.deckwrecka~", airwindohhs::deckwrecka::k_long_description.data());
}
