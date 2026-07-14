set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kcybercity_tilde) # output bundle: airfx.kcybercity~.mxo (_tilde->~)

target_sources(airfx.kcybercity_tilde
    PRIVATE
        airfx.kcybercity_tilde.cpp)

target_include_directories(airfx.kcybercity_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kcybercity_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
