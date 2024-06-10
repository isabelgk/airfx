#include "c74_min.h"
#include "airfx.hpp"
#include "effects/energy.hpp"

using namespace c74::min;

class energy_tilde : public airfx<energy_tilde, airwindohhs::energy::Energy<double>>
{
    atom m_about_text = symbol{ airwindohhs::energy::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::energy::k_name.data() };
    MIN_TAGS{ airwindohhs::energy::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    energy_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(energy_tilde);
