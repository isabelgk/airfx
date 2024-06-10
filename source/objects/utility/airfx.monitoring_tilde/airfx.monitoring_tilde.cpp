#include "c74_min.h"
#include "airfx.hpp"
#include "utility/monitoring.hpp"

using namespace c74::min;

class monitoring_tilde : public airfx<monitoring_tilde, airwindohhs::monitoring::Monitoring<double>>
{
    atom m_about_text = symbol{ airwindohhs::monitoring::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::monitoring::k_name.data() };
    MIN_TAGS{ airwindohhs::monitoring::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    monitoring_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(monitoring_tilde);
