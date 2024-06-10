#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/acceleration.hpp"

using namespace c74::min;

class acceleration_tilde : public airfx<acceleration_tilde, airwindohhs::acceleration::Acceleration<double>>
{
    atom m_about_text = symbol{ airwindohhs::acceleration::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::acceleration::k_name.data() };
    MIN_TAGS{ airwindohhs::acceleration::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    acceleration_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(acceleration_tilde);
