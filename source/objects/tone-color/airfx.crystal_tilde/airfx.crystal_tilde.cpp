#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/crystal.hpp"

using namespace c74::min;

class crystal_tilde : public airfx<crystal_tilde, airwindohhs::crystal::Crystal<double>>
{
    atom m_about_text = symbol{ airwindohhs::crystal::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::crystal::k_name.data() };
    MIN_TAGS{ airwindohhs::crystal::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    crystal_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(crystal_tilde);
