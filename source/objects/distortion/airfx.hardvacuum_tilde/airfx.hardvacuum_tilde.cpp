#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/hardvacuum.hpp"

using namespace c74::min;

class hardvacuum_tilde : public airfx<hardvacuum_tilde, airwindohhs::hardvacuum::HardVacuum<double>>
{
    atom m_about_text = symbol{ airwindohhs::hardvacuum::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::hardvacuum::k_name.data() };
    MIN_TAGS{ airwindohhs::hardvacuum::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    hardvacuum_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(hardvacuum_tilde);
