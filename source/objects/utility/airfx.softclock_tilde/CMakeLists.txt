set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.softclock_tilde) # output bundle: airfx.softclock~.mxo (_tilde->~)

target_sources(airfx.softclock_tilde
    PRIVATE
        airfx.softclock_tilde.cpp)

target_include_directories(airfx.softclock_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.softclock_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
