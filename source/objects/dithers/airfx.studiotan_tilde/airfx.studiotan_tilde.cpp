#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/studiotan.hpp"

using namespace c74::min;

class studiotan_tilde : public airfx<studiotan_tilde, airwindohhs::studiotan::StudioTan<double>>
{
    atom m_about_text = symbol{ airwindohhs::studiotan::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::studiotan::k_name.data() };
    MIN_TAGS{ airwindohhs::studiotan::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    studiotan_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(studiotan_tilde);
