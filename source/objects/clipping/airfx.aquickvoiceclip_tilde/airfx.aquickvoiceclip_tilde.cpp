#include "ext.h"

#include "airfx.hpp"
#include "clipping/aquickvoiceclip.hpp"

using TWrapped = airwindohhs::aquickvoiceclip::AQuickVoiceClip<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.aquickvoiceclip~", airwindohhs::aquickvoiceclip::k_long_description.data());
}
