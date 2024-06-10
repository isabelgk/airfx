#include "c74_min.h"
#include "airfx.hpp"
#include "filter/baxandall2.hpp"

using namespace c74::min;

class baxandall2_tilde : public airfx<baxandall2_tilde, airwindohhs::baxandall2::Baxandall2<double>>
{
    atom m_about_text = symbol{ airwindohhs::baxandall2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::baxandall2::k_name.data() };
    MIN_TAGS{ airwindohhs::baxandall2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    baxandall2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(baxandall2_tilde);
