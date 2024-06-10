#include "c74_min.h"
#include "airfx.hpp"
#include "utility/dcvoltage.hpp"

using namespace c74::min;

class dcvoltage_tilde : public airfx<dcvoltage_tilde, airwindohhs::dcvoltage::DCVoltage<double>>
{
    atom m_about_text = symbol{ airwindohhs::dcvoltage::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dcvoltage::k_name.data() };
    MIN_TAGS{ airwindohhs::dcvoltage::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dcvoltage_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dcvoltage_tilde);