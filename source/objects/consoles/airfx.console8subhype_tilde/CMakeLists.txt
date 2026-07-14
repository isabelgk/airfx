set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console8subhype_tilde) # output bundle: airfx.console8subhype~.mxo (_tilde->~)

target_sources(airfx.console8subhype_tilde
    PRIVATE
        airfx.console8subhype_tilde.cpp)

target_include_directories(airfx.console8subhype_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console8subhype_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
