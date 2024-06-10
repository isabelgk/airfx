#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/brassrider.hpp"

using namespace c74::min;

class brassrider_tilde : public airfx<brassrider_tilde, airwindohhs::brassrider::BrassRider<double>>
{
    atom m_about_text = symbol{ airwindohhs::brassrider::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::brassrider::k_name.data() };
    MIN_TAGS{ airwindohhs::brassrider::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    brassrider_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(brassrider_tilde);
