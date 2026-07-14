set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.elliptical_tilde) # output bundle: airfx.elliptical~.mxo (_tilde->~)

target_sources(airfx.elliptical_tilde
    PRIVATE
        airfx.elliptical_tilde.cpp)

target_include_directories(airfx.elliptical_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.elliptical_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
