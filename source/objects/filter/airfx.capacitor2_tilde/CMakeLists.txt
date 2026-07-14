set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.capacitor2_tilde) # output bundle: airfx.capacitor2~.mxo (_tilde->~)

target_sources(airfx.capacitor2_tilde
    PRIVATE
        airfx.capacitor2_tilde.cpp)

target_include_directories(airfx.capacitor2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.capacitor2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
