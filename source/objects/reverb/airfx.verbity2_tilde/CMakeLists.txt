set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.verbity2_tilde) # output bundle: airfx.verbity2~.mxo (_tilde->~)

target_sources(airfx.verbity2_tilde
    PRIVATE
        airfx.verbity2_tilde.cpp)

target_include_directories(airfx.verbity2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.verbity2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
