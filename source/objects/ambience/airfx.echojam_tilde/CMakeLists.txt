set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.echojam_tilde) # output bundle: airfx.echojam~.mxo (_tilde->~)

target_sources(airfx.echojam_tilde
    PRIVATE
        airfx.echojam_tilde.cpp)

target_include_directories(airfx.echojam_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.echojam_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
