set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.softclock2_tilde) # output bundle: airfx.softclock2~.mxo (_tilde->~)

target_sources(airfx.softclock2_tilde
    PRIVATE
        airfx.softclock2_tilde.cpp)

target_include_directories(airfx.softclock2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.softclock2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
