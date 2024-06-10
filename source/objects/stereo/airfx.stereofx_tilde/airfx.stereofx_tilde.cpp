#include "c74_min.h"
#include "airfx.hpp"
#include "stereo/stereofx.hpp"

using namespace c74::min;

class stereofx_tilde : public airfx<stereofx_tilde, airwindohhs::stereofx::StereoFX<double>>
{
    atom m_about_text = symbol{ airwindohhs::stereofx::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::stereofx::k_name.data() };
    MIN_TAGS{ airwindohhs::stereofx::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    stereofx_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(stereofx_tilde);
