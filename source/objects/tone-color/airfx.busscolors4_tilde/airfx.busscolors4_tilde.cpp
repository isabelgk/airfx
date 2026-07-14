#include "ext.h"

#include "airfx.hpp"
#include "tone-color/busscolors4.hpp"

using TWrapped = airwindohhs::busscolors4::BussColors4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.busscolors4~", airwindohhs::busscolors4::k_long_description.data());
}
