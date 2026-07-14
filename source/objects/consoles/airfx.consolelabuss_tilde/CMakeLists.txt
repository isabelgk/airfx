set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolelabuss_tilde) # output bundle: airfx.consolelabuss~.mxo (_tilde->~)

target_sources(airfx.consolelabuss_tilde
    PRIVATE
        airfx.consolelabuss_tilde.cpp)

target_include_directories(airfx.consolelabuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolelabuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
