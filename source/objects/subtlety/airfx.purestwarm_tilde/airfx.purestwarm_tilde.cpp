#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/purestwarm.hpp"

using namespace c74::min;

class purestwarm_tilde : public airfx<purestwarm_tilde, airwindohhs::purestwarm::PurestWarm<double>>
{
    atom m_about_text = symbol{ airwindohhs::purestwarm::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::purestwarm::k_name.data() };
    MIN_TAGS{ airwindohhs::purestwarm::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    purestwarm_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(purestwarm_tilde);
