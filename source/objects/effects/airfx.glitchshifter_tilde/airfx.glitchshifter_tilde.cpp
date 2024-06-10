#include "c74_min.h"
#include "airfx.hpp"
#include "effects/glitchshifter.hpp"

using namespace c74::min;

class glitchshifter_tilde : public airfx<glitchshifter_tilde, airwindohhs::glitchshifter::GlitchShifter<double>>
{
    atom m_about_text = symbol{ airwindohhs::glitchshifter::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::glitchshifter::k_name.data() };
    MIN_TAGS{ airwindohhs::glitchshifter::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    glitchshifter_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(glitchshifter_tilde);
