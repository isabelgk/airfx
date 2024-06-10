#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/buttercomp2.hpp"

using namespace c74::min;

class buttercomp2_tilde : public airfx<buttercomp2_tilde, airwindohhs::buttercomp2::ButterComp2<double>>
{
    atom m_about_text = symbol{ airwindohhs::buttercomp2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::buttercomp2::k_name.data() };
    MIN_TAGS{ airwindohhs::buttercomp2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    buttercomp2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(buttercomp2_tilde);
