#include "c74_min.h"
#include "airfx.hpp"
#include "bass/dubsub.hpp"

using namespace c74::min;

class dubsub_tilde : public airfx<dubsub_tilde, airwindohhs::dubsub::DubSub<double>>
{
    atom m_about_text = symbol{ airwindohhs::dubsub::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dubsub::k_name.data() };
    MIN_TAGS{ airwindohhs::dubsub::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dubsub_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dubsub_tilde);
