#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/varimu.hpp"

using namespace c74::min;

class varimu_tilde : public airfx<varimu_tilde, airwindohhs::varimu::VariMu<double>>
{
    atom m_about_text = symbol{ airwindohhs::varimu::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::varimu::k_name.data() };
    MIN_TAGS{ airwindohhs::varimu::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    varimu_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(varimu_tilde);
