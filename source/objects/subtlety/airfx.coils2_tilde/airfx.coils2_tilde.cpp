#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/coils2.hpp"

using namespace c74::min;

class coils2_tilde : public airfx<coils2_tilde, airwindohhs::coils2::Coils2<double>>
{
    atom m_about_text = symbol{ airwindohhs::coils2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::coils2::k_name.data() };
    MIN_TAGS{ airwindohhs::coils2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    coils2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(coils2_tilde);
