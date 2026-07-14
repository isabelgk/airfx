set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.density2_tilde) # output bundle: airfx.density2~.mxo (_tilde->~)

target_sources(airfx.density2_tilde
    PRIVATE
        airfx.density2_tilde.cpp)

target_include_directories(airfx.density2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.density2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
