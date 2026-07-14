set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestgain_tilde) # output bundle: airfx.purestgain~.mxo (_tilde->~)

target_sources(airfx.purestgain_tilde
    PRIVATE
        airfx.purestgain_tilde.cpp)

target_include_directories(airfx.purestgain_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestgain_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
