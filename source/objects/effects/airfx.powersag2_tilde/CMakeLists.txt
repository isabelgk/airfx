set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.powersag2_tilde) # output bundle: airfx.powersag2~.mxo (_tilde->~)

target_sources(airfx.powersag2_tilde
    PRIVATE
        airfx.powersag2_tilde.cpp)

target_include_directories(airfx.powersag2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.powersag2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
