#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/bite.hpp"

using namespace c74::min;

class bite_tilde : public airfx<bite_tilde, airwindohhs::bite::Bite<double>>
{
    atom m_about_text = symbol{ airwindohhs::bite::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::bite::k_name.data() };
    MIN_TAGS{ airwindohhs::bite::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    bite_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(bite_tilde);
