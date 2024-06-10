#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/interstage.hpp"

using namespace c74::min;

class interstage_tilde : public airfx<interstage_tilde, airwindohhs::interstage::Interstage<double>>
{
    atom m_about_text = symbol{ airwindohhs::interstage::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::interstage::k_name.data() };
    MIN_TAGS{ airwindohhs::interstage::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    interstage_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(interstage_tilde);
