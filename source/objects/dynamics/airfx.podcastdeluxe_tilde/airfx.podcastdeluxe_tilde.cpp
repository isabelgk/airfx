#include "ext.h"

#include "airfx.hpp"
#include "dynamics/podcastdeluxe.hpp"

using TWrapped = airwindohhs::podcastdeluxe::PodcastDeluxe<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.podcastdeluxe~", airwindohhs::podcastdeluxe::k_long_description.data());
}
