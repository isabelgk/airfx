set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bitshiftgain_tilde) # output bundle: airfx.bitshiftgain~.mxo (_tilde->~)

target_sources(airfx.bitshiftgain_tilde
    PRIVATE
        airfx.bitshiftgain_tilde.cpp)

target_include_directories(airfx.bitshiftgain_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bitshiftgain_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
