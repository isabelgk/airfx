#include "c74_min.h"
#include "airfx.hpp"
#include "noise/darknoise.hpp"

using namespace c74::min;

class darknoise_tilde : public airfx<darknoise_tilde, airwindohhs::darknoise::DarkNoise<double>>
{
    atom m_about_text = symbol{ airwindohhs::darknoise::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::darknoise::k_name.data() };
    MIN_TAGS{ airwindohhs::darknoise::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    darknoise_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(darknoise_tilde);
