set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.biquadhilo_tilde) # output bundle: airfx.biquadhilo~.mxo (_tilde->~)

target_sources(airfx.biquadhilo_tilde
    PRIVATE
        airfx.biquadhilo_tilde.cpp)

target_include_directories(airfx.biquadhilo_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.biquadhilo_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
