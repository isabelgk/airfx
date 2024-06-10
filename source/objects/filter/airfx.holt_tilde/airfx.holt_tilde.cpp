#include "c74_min.h"
#include "airfx.hpp"
#include "filter/holt.hpp"

using namespace c74::min;

class holt_tilde : public airfx<holt_tilde, airwindohhs::holt::Holt<double>>
{
    atom m_about_text = symbol{ airwindohhs::holt::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::holt::k_name.data() };
    MIN_TAGS{ airwindohhs::holt::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    holt_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(holt_tilde);
