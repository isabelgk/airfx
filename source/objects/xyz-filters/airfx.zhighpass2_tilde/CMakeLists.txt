set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zhighpass2_tilde) # output bundle: airfx.zhighpass2~.mxo (_tilde->~)

target_sources(airfx.zhighpass2_tilde
    PRIVATE
        airfx.zhighpass2_tilde.cpp)

target_include_directories(airfx.zhighpass2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zhighpass2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
