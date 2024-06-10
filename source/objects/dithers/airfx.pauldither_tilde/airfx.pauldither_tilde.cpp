#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/pauldither.hpp"

using namespace c74::min;

class pauldither_tilde : public airfx<pauldither_tilde, airwindohhs::pauldither::PaulDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::pauldither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pauldither::k_name.data() };
    MIN_TAGS{ airwindohhs::pauldither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pauldither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pauldither_tilde);
