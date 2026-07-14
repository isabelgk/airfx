set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.softclock3_tilde) # output bundle: airfx.softclock3~.mxo (_tilde->~)

target_sources(airfx.softclock3_tilde
    PRIVATE
        airfx.softclock3_tilde.cpp)

target_include_directories(airfx.softclock3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.softclock3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
