#include "c74_min.h"
#include "airfx.hpp"
#include "bass/orbitkick.hpp"

using namespace c74::min;

class orbitkick_tilde : public airfx<orbitkick_tilde, airwindohhs::orbitkick::OrbitKick<double>>
{
    atom m_about_text = symbol{ airwindohhs::orbitkick::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::orbitkick::k_name.data() };
    MIN_TAGS{ airwindohhs::orbitkick::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    orbitkick_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(orbitkick_tilde);
