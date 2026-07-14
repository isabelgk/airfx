set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.powersag_tilde) # output bundle: airfx.powersag~.mxo (_tilde->~)

target_sources(airfx.powersag_tilde
    PRIVATE
        airfx.powersag_tilde.cpp)

target_include_directories(airfx.powersag_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.powersag_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
