#include "c74_min.h"
#include "airfx.hpp"
#include "noise/voiceofthestarship.hpp"

using namespace c74::min;

class voiceofthestarship_tilde : public airfx<voiceofthestarship_tilde, airwindohhs::voiceofthestarship::VoiceOfTheStarship<double>>
{
    atom m_about_text = symbol{ airwindohhs::voiceofthestarship::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::voiceofthestarship::k_name.data() };
    MIN_TAGS{ airwindohhs::voiceofthestarship::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    voiceofthestarship_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(voiceofthestarship_tilde);
