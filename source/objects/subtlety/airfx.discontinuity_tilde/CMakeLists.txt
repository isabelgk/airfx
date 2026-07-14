set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.discontinuity_tilde) # output bundle: airfx.discontinuity~.mxo (_tilde->~)

target_sources(airfx.discontinuity_tilde
    PRIVATE
        airfx.discontinuity_tilde.cpp)

target_include_directories(airfx.discontinuity_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.discontinuity_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
