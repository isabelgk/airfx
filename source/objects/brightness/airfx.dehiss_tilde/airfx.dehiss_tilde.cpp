#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/dehiss.hpp"

using namespace c74::min;

class dehiss_tilde : public airfx<dehiss_tilde, airwindohhs::dehiss::DeHiss<double>>
{
    atom m_about_text = symbol{ airwindohhs::dehiss::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dehiss::k_name.data() };
    MIN_TAGS{ airwindohhs::dehiss::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dehiss_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dehiss_tilde);
