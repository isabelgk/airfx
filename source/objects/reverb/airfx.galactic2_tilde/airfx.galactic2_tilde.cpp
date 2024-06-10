#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/galactic2.hpp"

using namespace c74::min;

class galactic2_tilde : public airfx<galactic2_tilde, airwindohhs::galactic2::Galactic2<double>>
{
    atom m_about_text = symbol{ airwindohhs::galactic2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::galactic2::k_name.data() };
    MIN_TAGS{ airwindohhs::galactic2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    galactic2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(galactic2_tilde);
