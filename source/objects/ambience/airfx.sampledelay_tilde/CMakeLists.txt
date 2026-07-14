set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.sampledelay_tilde) # output bundle: airfx.sampledelay~.mxo (_tilde->~)

target_sources(airfx.sampledelay_tilde
    PRIVATE
        airfx.sampledelay_tilde.cpp)

target_include_directories(airfx.sampledelay_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.sampledelay_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
