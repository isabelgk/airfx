#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/tapedelay.hpp"

using namespace c74::min;

class tapedelay_tilde : public airfx<tapedelay_tilde, airwindohhs::tapedelay::TapeDelay<double>>
{
    atom m_about_text = symbol{ airwindohhs::tapedelay::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tapedelay::k_name.data() };
    MIN_TAGS{ airwindohhs::tapedelay::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tapedelay_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tapedelay_tilde);
