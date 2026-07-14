set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zbandpass2_tilde) # output bundle: airfx.zbandpass2~.mxo (_tilde->~)

target_sources(airfx.zbandpass2_tilde
    PRIVATE
        airfx.zbandpass2_tilde.cpp)

target_include_directories(airfx.zbandpass2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zbandpass2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
