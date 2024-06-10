#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/mv2.hpp"

using namespace c74::min;

class mv2_tilde : public airfx<mv2_tilde, airwindohhs::mv2::MV2<double>>
{
    atom m_about_text = symbol{ airwindohhs::mv2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::mv2::k_name.data() };
    MIN_TAGS{ airwindohhs::mv2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    mv2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(mv2_tilde);
