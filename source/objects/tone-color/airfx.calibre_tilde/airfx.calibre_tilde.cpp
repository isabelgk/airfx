#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/calibre.hpp"

using namespace c74::min;

class calibre_tilde : public airfx<calibre_tilde, airwindohhs::calibre::Calibre<double>>
{
    atom m_about_text = symbol{ airwindohhs::calibre::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::calibre::k_name.data() };
    MIN_TAGS{ airwindohhs::calibre::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    calibre_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(calibre_tilde);
