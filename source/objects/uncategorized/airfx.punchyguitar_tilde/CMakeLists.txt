set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.punchyguitar_tilde) # output bundle: airfx.punchyguitar~.mxo (_tilde->~)

target_sources(airfx.punchyguitar_tilde
    PRIVATE
        airfx.punchyguitar_tilde.cpp)

target_include_directories(airfx.punchyguitar_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.punchyguitar_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
