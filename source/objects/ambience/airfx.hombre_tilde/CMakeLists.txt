set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hombre_tilde) # output bundle: airfx.hombre~.mxo (_tilde->~)

target_sources(airfx.hombre_tilde
    PRIVATE
        airfx.hombre_tilde.cpp)

target_include_directories(airfx.hombre_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hombre_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
