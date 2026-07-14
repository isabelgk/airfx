set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pop2_tilde) # output bundle: airfx.pop2~.mxo (_tilde->~)

target_sources(airfx.pop2_tilde
    PRIVATE
        airfx.pop2_tilde.cpp)

target_include_directories(airfx.pop2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pop2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
