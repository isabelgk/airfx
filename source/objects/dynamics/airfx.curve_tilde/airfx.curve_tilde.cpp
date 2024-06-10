#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/curve.hpp"

using namespace c74::min;

class curve_tilde : public airfx<curve_tilde, airwindohhs::curve::curve<double>>
{
    atom m_about_text = symbol{ airwindohhs::curve::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::curve::k_name.data() };
    MIN_TAGS{ airwindohhs::curve::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    curve_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(curve_tilde);
