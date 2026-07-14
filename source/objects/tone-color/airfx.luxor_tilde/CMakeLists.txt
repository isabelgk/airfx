set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.luxor_tilde) # output bundle: airfx.luxor~.mxo (_tilde->~)

target_sources(airfx.luxor_tilde
    PRIVATE
        airfx.luxor_tilde.cpp)

target_include_directories(airfx.luxor_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.luxor_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
