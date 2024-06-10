#include "c74_min.h"
#include "airfx.hpp"
#include "noise/noise.hpp"

using namespace c74::min;

class noise_tilde : public airfx<noise_tilde, airwindohhs::noise::Noise<double>>
{
    atom m_about_text = symbol{ airwindohhs::noise::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::noise::k_name.data() };
    MIN_TAGS{ airwindohhs::noise::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    noise_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(noise_tilde);
