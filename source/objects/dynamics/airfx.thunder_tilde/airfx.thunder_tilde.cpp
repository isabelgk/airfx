#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/thunder.hpp"

using namespace c74::min;

class thunder_tilde : public airfx<thunder_tilde, airwindohhs::thunder::Thunder<double>>
{
    atom m_about_text = symbol{ airwindohhs::thunder::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::thunder::k_name.data() };
    MIN_TAGS{ airwindohhs::thunder::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    thunder_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(thunder_tilde);
