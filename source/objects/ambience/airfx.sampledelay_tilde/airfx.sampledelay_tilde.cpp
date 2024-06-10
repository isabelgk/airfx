#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/sampledelay.hpp"

using namespace c74::min;

class sampledelay_tilde : public airfx<sampledelay_tilde, airwindohhs::sampledelay::SampleDelay<double>>
{
    atom m_about_text = symbol{ airwindohhs::sampledelay::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::sampledelay::k_name.data() };
    MIN_TAGS{ airwindohhs::sampledelay::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    sampledelay_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(sampledelay_tilde);
