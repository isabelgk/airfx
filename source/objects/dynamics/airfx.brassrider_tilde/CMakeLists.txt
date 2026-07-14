set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.brassrider_tilde) # output bundle: airfx.brassrider~.mxo (_tilde->~)

target_sources(airfx.brassrider_tilde
    PRIVATE
        airfx.brassrider_tilde.cpp)

target_include_directories(airfx.brassrider_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.brassrider_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
