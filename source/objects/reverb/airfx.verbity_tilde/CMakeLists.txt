set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.verbity_tilde) # output bundle: airfx.verbity~.mxo (_tilde->~)

target_sources(airfx.verbity_tilde
    PRIVATE
        airfx.verbity_tilde.cpp)

target_include_directories(airfx.verbity_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.verbity_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
