set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.biquadonehalf_tilde) # output bundle: airfx.biquadonehalf~.mxo (_tilde->~)

target_sources(airfx.biquadonehalf_tilde
    PRIVATE
        airfx.biquadonehalf_tilde.cpp)

target_include_directories(airfx.biquadonehalf_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.biquadonehalf_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
