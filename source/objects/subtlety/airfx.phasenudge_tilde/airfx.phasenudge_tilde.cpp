#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/phasenudge.hpp"

using namespace c74::min;

class phasenudge_tilde : public airfx<phasenudge_tilde, airwindohhs::phasenudge::PhaseNudge<double>>
{
    atom m_about_text = symbol{ airwindohhs::phasenudge::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::phasenudge::k_name.data() };
    MIN_TAGS{ airwindohhs::phasenudge::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    phasenudge_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(phasenudge_tilde);
