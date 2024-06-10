#include "c74_min.h"
#include "airfx.hpp"
#include "bass/infrasonic.hpp"

using namespace c74::min;

class infrasonic_tilde : public airfx<infrasonic_tilde, airwindohhs::infrasonic::Infrasonic<double>>
{
    atom m_about_text = symbol{ airwindohhs::infrasonic::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::infrasonic::k_name.data() };
    MIN_TAGS{ airwindohhs::infrasonic::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    infrasonic_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(infrasonic_tilde);
