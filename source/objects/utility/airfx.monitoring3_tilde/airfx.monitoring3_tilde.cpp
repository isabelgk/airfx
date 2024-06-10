#include "c74_min.h"
#include "airfx.hpp"
#include "utility/monitoring3.hpp"

using namespace c74::min;

class monitoring3_tilde : public airfx<monitoring3_tilde, airwindohhs::monitoring3::Monitoring3<double>>
{
    atom m_about_text = symbol{ airwindohhs::monitoring3::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::monitoring3::k_name.data() };
    MIN_TAGS{ airwindohhs::monitoring3::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    monitoring3_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(monitoring3_tilde);
