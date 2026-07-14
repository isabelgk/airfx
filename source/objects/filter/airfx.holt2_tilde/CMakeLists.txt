set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.holt2_tilde) # output bundle: airfx.holt2~.mxo (_tilde->~)

target_sources(airfx.holt2_tilde
    PRIVATE
        airfx.holt2_tilde.cpp)

target_include_directories(airfx.holt2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.holt2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
