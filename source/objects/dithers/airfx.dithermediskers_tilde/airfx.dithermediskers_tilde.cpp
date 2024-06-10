#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/dithermediskers.hpp"

using namespace c74::min;

class dithermediskers_tilde : public airfx<dithermediskers_tilde, airwindohhs::dithermediskers::DitherMeDiskers<double>>
{
    atom m_about_text = symbol{ airwindohhs::dithermediskers::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dithermediskers::k_name.data() };
    MIN_TAGS{ airwindohhs::dithermediskers::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dithermediskers_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dithermediskers_tilde);
