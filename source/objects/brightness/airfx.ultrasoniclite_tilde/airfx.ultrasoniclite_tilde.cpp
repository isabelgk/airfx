#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/ultrasoniclite.hpp"

using namespace c74::min;

class ultrasoniclite_tilde : public airfx<ultrasoniclite_tilde, airwindohhs::ultrasoniclite::UltrasonicLite<double>>
{
    atom m_about_text = symbol{ airwindohhs::ultrasoniclite::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ultrasoniclite::k_name.data() };
    MIN_TAGS{ airwindohhs::ultrasoniclite::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ultrasoniclite_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ultrasoniclite_tilde);
