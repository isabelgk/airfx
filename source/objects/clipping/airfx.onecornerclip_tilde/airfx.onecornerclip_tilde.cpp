#include "ext.h"

#include "airfx.hpp"
#include "clipping/onecornerclip.hpp"

using TWrapped = airwindohhs::onecornerclip::OneCornerClip<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.onecornerclip~", airwindohhs::onecornerclip::k_long_description.data());
}
