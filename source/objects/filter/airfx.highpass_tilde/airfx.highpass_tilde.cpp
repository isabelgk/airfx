#include "c74_min.h"
#include "airfx.hpp"
#include "filter/highpass.hpp"

using namespace c74::min;

class highpass_tilde : public airfx<highpass_tilde, airwindohhs::highpass::Highpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::highpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::highpass::k_name.data() };
    MIN_TAGS{ airwindohhs::highpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    highpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(highpass_tilde);
