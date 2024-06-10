#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/swell.hpp"

using namespace c74::min;

class swell_tilde : public airfx<swell_tilde, airwindohhs::swell::Swell<double>>
{
    atom m_about_text = symbol{ airwindohhs::swell::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::swell::k_name.data() };
    MIN_TAGS{ airwindohhs::swell::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    swell_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(swell_tilde);
