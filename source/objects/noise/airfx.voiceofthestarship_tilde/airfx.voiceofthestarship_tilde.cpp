#include "ext.h"

#include "airfx.hpp"
#include "noise/voiceofthestarship.hpp"

using TWrapped = airwindohhs::voiceofthestarship::VoiceOfTheStarship<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.voiceofthestarship~", airwindohhs::voiceofthestarship::k_long_description.data());
}
