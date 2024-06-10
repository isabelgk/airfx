#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/tapedither.hpp"

using namespace c74::min;

class tapedither_tilde : public airfx<tapedither_tilde, airwindohhs::tapedither::TapeDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::tapedither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tapedither::k_name.data() };
    MIN_TAGS{ airwindohhs::tapedither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tapedither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tapedither_tilde);
