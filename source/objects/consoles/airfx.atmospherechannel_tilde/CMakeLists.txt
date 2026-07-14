set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.atmospherechannel_tilde) # output bundle: airfx.atmospherechannel~.mxo (_tilde->~)

target_sources(airfx.atmospherechannel_tilde
    PRIVATE
        airfx.atmospherechannel_tilde.cpp)

target_include_directories(airfx.atmospherechannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.atmospherechannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
