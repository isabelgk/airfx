set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.capacitor_tilde) # output bundle: airfx.capacitor~.mxo (_tilde->~)

target_sources(airfx.capacitor_tilde
    PRIVATE
        airfx.capacitor_tilde.cpp)

target_include_directories(airfx.capacitor_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.capacitor_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
