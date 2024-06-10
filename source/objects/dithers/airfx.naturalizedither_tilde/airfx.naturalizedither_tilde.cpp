#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/naturalizedither.hpp"

using namespace c74::min;

class naturalizedither_tilde : public airfx<naturalizedither_tilde, airwindohhs::naturalizedither::NaturalizeDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::naturalizedither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::naturalizedither::k_name.data() };
    MIN_TAGS{ airwindohhs::naturalizedither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    naturalizedither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(naturalizedither_tilde);
