#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/dirt.hpp"

using namespace c74::min;

class dirt_tilde : public airfx<dirt_tilde, airwindohhs::dirt::Dirt<double>>
{
    atom m_about_text = symbol{ airwindohhs::dirt::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dirt::k_name.data() };
    MIN_TAGS{ airwindohhs::dirt::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dirt_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dirt_tilde);
