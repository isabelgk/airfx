#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/zoutputstage.hpp"

using namespace c74::min;

class zoutputstage_tilde : public airfx<zoutputstage_tilde, airwindohhs::zoutputstage::ZOutputStage<double>>
{
    atom m_about_text = symbol{ airwindohhs::zoutputstage::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::zoutputstage::k_name.data() };
    MIN_TAGS{ airwindohhs::zoutputstage::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    zoutputstage_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(zoutputstage_tilde);
