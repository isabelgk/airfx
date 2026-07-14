set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.stereodoubler_tilde) # output bundle: airfx.stereodoubler~.mxo (_tilde->~)

target_sources(airfx.stereodoubler_tilde
    PRIVATE
        airfx.stereodoubler_tilde.cpp)

target_include_directories(airfx.stereodoubler_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.stereodoubler_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
