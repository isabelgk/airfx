#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/dithermetimbers.hpp"

using namespace c74::min;

class dithermetimbers_tilde : public airfx<dithermetimbers_tilde, airwindohhs::dithermetimbers::DitherMeTimbers<double>>
{
    atom m_about_text = symbol{ airwindohhs::dithermetimbers::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dithermetimbers::k_name.data() };
    MIN_TAGS{ airwindohhs::dithermetimbers::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dithermetimbers_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dithermetimbers_tilde);
