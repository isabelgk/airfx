#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/brightambience2.hpp"

using namespace c74::min;

class brightambience2_tilde : public airfx<brightambience2_tilde, airwindohhs::brightambience2::BrightAmbience2<double>>
{
    atom m_about_text = symbol{ airwindohhs::brightambience2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::brightambience2::k_name.data() };
    MIN_TAGS{ airwindohhs::brightambience2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    brightambience2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(brightambience2_tilde);
