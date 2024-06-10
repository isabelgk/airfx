#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/dynamics.hpp"

using namespace c74::min;

class dynamics_tilde : public airfx<dynamics_tilde, airwindohhs::dynamics::Dynamics<double>>
{
    atom m_about_text = symbol{ airwindohhs::dynamics::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dynamics::k_name.data() };
    MIN_TAGS{ airwindohhs::dynamics::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dynamics_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dynamics_tilde);
