#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/purestwarm2.hpp"

using namespace c74::min;

class purestwarm2_tilde : public airfx<purestwarm2_tilde, airwindohhs::purestwarm2::PurestWarm2<double>>
{
    atom m_about_text = symbol{ airwindohhs::purestwarm2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::purestwarm2::k_name.data() };
    MIN_TAGS{ airwindohhs::purestwarm2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    purestwarm2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(purestwarm2_tilde);
