set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pitchdelay_tilde) # output bundle: airfx.pitchdelay~.mxo (_tilde->~)

target_sources(airfx.pitchdelay_tilde
    PRIVATE
        airfx.pitchdelay_tilde.cpp)

target_include_directories(airfx.pitchdelay_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pitchdelay_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
