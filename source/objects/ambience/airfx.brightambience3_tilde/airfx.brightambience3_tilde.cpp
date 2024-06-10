#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/brightambience3.hpp"

using namespace c74::min;

class brightambience3_tilde : public airfx<brightambience3_tilde, airwindohhs::brightambience3::BrightAmbience3<double>>
{
    atom m_about_text = symbol{ airwindohhs::brightambience3::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::brightambience3::k_name.data() };
    MIN_TAGS{ airwindohhs::brightambience3::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    brightambience3_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(brightambience3_tilde);
