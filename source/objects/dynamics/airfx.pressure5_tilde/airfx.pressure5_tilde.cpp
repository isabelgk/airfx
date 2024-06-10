#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/pressure5.hpp"

using namespace c74::min;

class pressure5_tilde : public airfx<pressure5_tilde, airwindohhs::pressure5::Pressure5<double>>
{
    atom m_about_text = symbol{ airwindohhs::pressure5::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pressure5::k_name.data() };
    MIN_TAGS{ airwindohhs::pressure5::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pressure5_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pressure5_tilde);
