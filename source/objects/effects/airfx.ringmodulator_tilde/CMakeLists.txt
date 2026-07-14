set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ringmodulator_tilde) # output bundle: airfx.ringmodulator~.mxo (_tilde->~)

target_sources(airfx.ringmodulator_tilde
    PRIVATE
        airfx.ringmodulator_tilde.cpp)

target_include_directories(airfx.ringmodulator_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ringmodulator_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
