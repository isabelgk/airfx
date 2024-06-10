#include "c74_min.h"
#include "airfx.hpp"
#include "tape/ironoxideclassic.hpp"

using namespace c74::min;

class ironoxideclassic_tilde : public airfx<ironoxideclassic_tilde, airwindohhs::ironoxideclassic::IronOxideClassic<double>>
{
    atom m_about_text = symbol{ airwindohhs::ironoxideclassic::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ironoxideclassic::k_name.data() };
    MIN_TAGS{ airwindohhs::ironoxideclassic::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ironoxideclassic_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ironoxideclassic_tilde);
