#include "c74_min.h"
#include "airfx.hpp"
#include "effects/pitchnasty.hpp"

using namespace c74::min;

class pitchnasty_tilde : public airfx<pitchnasty_tilde, airwindohhs::pitchnasty::PitchNasty<double>>
{
    atom m_about_text = symbol{ airwindohhs::pitchnasty::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pitchnasty::k_name.data() };
    MIN_TAGS{ airwindohhs::pitchnasty::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pitchnasty_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pitchnasty_tilde);
