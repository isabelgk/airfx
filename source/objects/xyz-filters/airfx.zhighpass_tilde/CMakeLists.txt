set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zhighpass_tilde) # output bundle: airfx.zhighpass~.mxo (_tilde->~)

target_sources(airfx.zhighpass_tilde
    PRIVATE
        airfx.zhighpass_tilde.cpp)

target_include_directories(airfx.zhighpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zhighpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
