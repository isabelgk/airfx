#include "c74_min.h"
#include "airfx.hpp"
#include "bass/dubcenter.hpp"

using namespace c74::min;

class dubcenter_tilde : public airfx<dubcenter_tilde, airwindohhs::dubcenter::DubCenter<double>>
{
    atom m_about_text = symbol{ airwindohhs::dubcenter::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dubcenter::k_name.data() };
    MIN_TAGS{ airwindohhs::dubcenter::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dubcenter_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dubcenter_tilde);
