#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/stereochorus.hpp"

using namespace c74::min;

class stereochorus_tilde : public airfx<stereochorus_tilde, airwindohhs::stereochorus::StereoChorus<double>>
{
    atom m_about_text = symbol{ airwindohhs::stereochorus::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::stereochorus::k_name.data() };
    MIN_TAGS{ airwindohhs::stereochorus::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    stereochorus_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(stereochorus_tilde);
