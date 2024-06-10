#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/drumslam.hpp"

using namespace c74::min;

class drumslam_tilde : public airfx<drumslam_tilde, airwindohhs::drumslam::DrumSlam<double>>
{
    atom m_about_text = symbol{ airwindohhs::drumslam::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::drumslam::k_name.data() };
    MIN_TAGS{ airwindohhs::drumslam::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    drumslam_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(drumslam_tilde);
