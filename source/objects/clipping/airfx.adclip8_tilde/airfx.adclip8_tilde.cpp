#include "c74_min.h"
#include "airfx.hpp"
#include "clipping/adclip8.hpp"

using namespace c74::min;

class adclip8_tilde : public airfx<adclip8_tilde, airwindohhs::adclip8::ADClip8<double>>
{
    atom m_about_text = symbol{ airwindohhs::adclip8::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::adclip8::k_name.data() };
    MIN_TAGS{ airwindohhs::adclip8::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    adclip8_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(adclip8_tilde);
