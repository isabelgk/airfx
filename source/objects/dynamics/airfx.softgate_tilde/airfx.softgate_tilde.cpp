#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/softgate.hpp"

using namespace c74::min;

class softgate_tilde : public airfx<softgate_tilde, airwindohhs::softgate::SoftGate<double>>
{
    atom m_about_text = symbol{ airwindohhs::softgate::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::softgate::k_name.data() };
    MIN_TAGS{ airwindohhs::softgate::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    softgate_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(softgate_tilde);
