#include "ext.h"

#include "airfx.hpp"
#include "dynamics/podcast.hpp"

using TWrapped = airwindohhs::podcast::Podcast<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.podcast~", airwindohhs::podcast::k_long_description.data());
}
