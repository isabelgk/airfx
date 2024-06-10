#include "c74_min.h"
#include "airfx.hpp"
#include "effects/fracture2.hpp"

using namespace c74::min;

class fracture2_tilde : public airfx<fracture2_tilde, airwindohhs::fracture2::Fracture2<double>>
{
    atom m_about_text = symbol{ airwindohhs::fracture2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::fracture2::k_name.data() };
    MIN_TAGS{ airwindohhs::fracture2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    fracture2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(fracture2_tilde);
