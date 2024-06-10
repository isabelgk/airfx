#include "c74_min.h"
#include "airfx.hpp"
#include "clipping/onecornerclip.hpp"

using namespace c74::min;

class onecornerclip_tilde : public airfx<onecornerclip_tilde, airwindohhs::onecornerclip::OneCornerClip<double>>
{
    atom m_about_text = symbol{ airwindohhs::onecornerclip::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::onecornerclip::k_name.data() };
    MIN_TAGS{ airwindohhs::onecornerclip::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    onecornerclip_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(onecornerclip_tilde);
