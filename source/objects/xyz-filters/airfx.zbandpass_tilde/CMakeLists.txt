set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zbandpass_tilde) # output bundle: airfx.zbandpass~.mxo (_tilde->~)

target_sources(airfx.zbandpass_tilde
    PRIVATE
        airfx.zbandpass_tilde.cpp)

target_include_directories(airfx.zbandpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zbandpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
