#include "c74_min.h"
#include "airfx.hpp"
#include "amp-sims/cabs.hpp"

using namespace c74::min;

class cabs_tilde : public airfx<cabs_tilde, airwindohhs::cabs::Cabs<double>>
{
    atom m_about_text = symbol{ airwindohhs::cabs::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::cabs::k_name.data() };
    MIN_TAGS{ airwindohhs::cabs::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    cabs_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(cabs_tilde);
