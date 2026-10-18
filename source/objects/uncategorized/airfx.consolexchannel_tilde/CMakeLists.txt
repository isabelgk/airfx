set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolexchannel_tilde) # output bundle: airfx.consolexchannel~.mxo (_tilde->~)

target_sources(airfx.consolexchannel_tilde
    PRIVATE
        airfx.consolexchannel_tilde.cpp)

target_include_directories(airfx.consolexchannel_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolexchannel_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
