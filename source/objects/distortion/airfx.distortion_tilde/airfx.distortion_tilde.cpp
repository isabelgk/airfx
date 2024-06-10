#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/distortion.hpp"

using namespace c74::min;

class distortion_tilde : public airfx<distortion_tilde, airwindohhs::distortion::Distortion<double>>
{
    atom m_about_text = symbol{ airwindohhs::distortion::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::distortion::k_name.data() };
    MIN_TAGS{ airwindohhs::distortion::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    distortion_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(distortion_tilde);
