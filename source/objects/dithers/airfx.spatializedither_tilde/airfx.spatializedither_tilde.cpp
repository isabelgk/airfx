#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/spatializedither.hpp"

using namespace c74::min;

class spatializedither_tilde : public airfx<spatializedither_tilde, airwindohhs::spatializedither::SpatializeDither<double>>
{
    atom m_about_text = symbol{ airwindohhs::spatializedither::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::spatializedither::k_name.data() };
    MIN_TAGS{ airwindohhs::spatializedither::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    spatializedither_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(spatializedither_tilde);
