#include "c74_min.h"
#include "airfx.hpp"
#include "filter/lowpass2.hpp"

using namespace c74::min;

class lowpass2_tilde : public airfx<lowpass2_tilde, airwindohhs::lowpass2::Lowpass2<double>>
{
    atom m_about_text = symbol{ airwindohhs::lowpass2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::lowpass2::k_name.data() };
    MIN_TAGS{ airwindohhs::lowpass2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    lowpass2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(lowpass2_tilde);
