#include "c74_min.h"
#include "airfx.hpp"
#include "filter/baxandall.hpp"

using namespace c74::min;

class baxandall_tilde : public airfx<baxandall_tilde, airwindohhs::baxandall::Baxandall<double>>
{
    atom m_about_text = symbol{ airwindohhs::baxandall::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::baxandall::k_name.data() };
    MIN_TAGS{ airwindohhs::baxandall::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    baxandall_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(baxandall_tilde);
