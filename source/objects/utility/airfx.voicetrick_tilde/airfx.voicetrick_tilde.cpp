#include "c74_min.h"
#include "airfx.hpp"
#include "utility/voicetrick.hpp"

using namespace c74::min;

class voicetrick_tilde : public airfx<voicetrick_tilde, airwindohhs::voicetrick::VoiceTrick<double>>
{
    atom m_about_text = symbol{ airwindohhs::voicetrick::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::voicetrick::k_name.data() };
    MIN_TAGS{ airwindohhs::voicetrick::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    voicetrick_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(voicetrick_tilde);
