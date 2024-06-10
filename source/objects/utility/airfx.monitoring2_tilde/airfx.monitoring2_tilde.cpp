#include "c74_min.h"
#include "airfx.hpp"
#include "utility/monitoring2.hpp"

using namespace c74::min;

class monitoring2_tilde : public airfx<monitoring2_tilde, airwindohhs::monitoring2::Monitoring2<double>>
{
    atom m_about_text = symbol{ airwindohhs::monitoring2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::monitoring2::k_name.data() };
    MIN_TAGS{ airwindohhs::monitoring2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    monitoring2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(monitoring2_tilde);
