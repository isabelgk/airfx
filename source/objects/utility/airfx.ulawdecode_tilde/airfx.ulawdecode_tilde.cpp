#include "c74_min.h"
#include "airfx.hpp"
#include "utility/ulawdecode.hpp"

using namespace c74::min;

class ulawdecode_tilde : public airfx<ulawdecode_tilde, airwindohhs::ulawdecode::uLawDecode<double>>
{
    atom m_about_text = symbol{ airwindohhs::ulawdecode::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ulawdecode::k_name.data() };
    MIN_TAGS{ airwindohhs::ulawdecode::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ulawdecode_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ulawdecode_tilde);
