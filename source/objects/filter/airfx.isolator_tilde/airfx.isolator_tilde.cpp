#include "c74_min.h"
#include "airfx.hpp"
#include "filter/isolator.hpp"

using namespace c74::min;

class isolator_tilde : public airfx<isolator_tilde, airwindohhs::isolator::Isolator<double>>
{
    atom m_about_text = symbol{ airwindohhs::isolator::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::isolator::k_name.data() };
    MIN_TAGS{ airwindohhs::isolator::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    isolator_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(isolator_tilde);
