#include "c74_min.h"
#include "airfx.hpp"
#include "filter/lowpass.hpp"

using namespace c74::min;

class lowpass_tilde : public airfx<lowpass_tilde, airwindohhs::lowpass::Lowpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::lowpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::lowpass::k_name.data() };
    MIN_TAGS{ airwindohhs::lowpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    lowpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(lowpass_tilde);
