set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ynotlowpass_tilde) # output bundle: airfx.ynotlowpass~.mxo (_tilde->~)

target_sources(airfx.ynotlowpass_tilde
    PRIVATE
        airfx.ynotlowpass_tilde.cpp)

target_include_directories(airfx.ynotlowpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ynotlowpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
