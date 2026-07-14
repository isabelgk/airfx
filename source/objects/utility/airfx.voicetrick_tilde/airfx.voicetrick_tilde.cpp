#include "ext.h"

#include "airfx.hpp"
#include "utility/voicetrick.hpp"

using TWrapped = airwindohhs::voicetrick::VoiceTrick<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.voicetrick~", airwindohhs::voicetrick::k_long_description.data());
}
