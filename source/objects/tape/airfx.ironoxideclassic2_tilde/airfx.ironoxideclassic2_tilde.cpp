#include "c74_min.h"
#include "airfx.hpp"
#include "tape/ironoxideclassic2.hpp"

using namespace c74::min;

class ironoxideclassic2_tilde : public airfx<ironoxideclassic2_tilde, airwindohhs::ironoxideclassic2::IronOxideClassic2<double>>
{
    atom m_about_text = symbol{ airwindohhs::ironoxideclassic2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ironoxideclassic2::k_name.data() };
    MIN_TAGS{ airwindohhs::ironoxideclassic2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ironoxideclassic2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ironoxideclassic2_tilde);
