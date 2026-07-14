set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.slewsonic_tilde) # output bundle: airfx.slewsonic~.mxo (_tilde->~)

target_sources(airfx.slewsonic_tilde
    PRIVATE
        airfx.slewsonic_tilde.cpp)

target_include_directories(airfx.slewsonic_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.slewsonic_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
