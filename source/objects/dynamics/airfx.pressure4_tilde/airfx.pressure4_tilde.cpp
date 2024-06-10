#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/pressure4.hpp"

using namespace c74::min;

class pressure4_tilde : public airfx<pressure4_tilde, airwindohhs::pressure4::Pressure4<double>>
{
    atom m_about_text = symbol{ airwindohhs::pressure4::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pressure4::k_name.data() };
    MIN_TAGS{ airwindohhs::pressure4::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pressure4_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pressure4_tilde);
