#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/pitchdelay.hpp"

using namespace c74::min;

class pitchdelay_tilde : public airfx<pitchdelay_tilde, airwindohhs::pitchdelay::PitchDelay<double>>
{
    atom m_about_text = symbol{ airwindohhs::pitchdelay::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pitchdelay::k_name.data() };
    MIN_TAGS{ airwindohhs::pitchdelay::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pitchdelay_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pitchdelay_tilde);
