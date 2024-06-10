#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/compresaturator.hpp"

using namespace c74::min;

class compresaturator_tilde : public airfx<compresaturator_tilde, airwindohhs::compresaturator::Compresaturator<double>>
{
    atom m_about_text = symbol{ airwindohhs::compresaturator::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::compresaturator::k_name.data() };
    MIN_TAGS{ airwindohhs::compresaturator::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    compresaturator_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(compresaturator_tilde);
