#include "c74_min.h"
#include "airfx.hpp"
#include "utility/edisdim.hpp"

using namespace c74::min;

class edisdim_tilde : public airfx<edisdim_tilde, airwindohhs::edisdim::EdIsDim<double>>
{
    atom m_about_text = symbol{ airwindohhs::edisdim::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::edisdim::k_name.data() };
    MIN_TAGS{ airwindohhs::edisdim::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    edisdim_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(edisdim_tilde);
