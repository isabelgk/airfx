set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dcvoltage_tilde) # output bundle: airfx.dcvoltage~.mxo (_tilde->~)

target_sources(airfx.dcvoltage_tilde
    PRIVATE
        airfx.dcvoltage_tilde.cpp)

target_include_directories(airfx.dcvoltage_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dcvoltage_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
