set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.electrohat_tilde) # output bundle: airfx.electrohat~.mxo (_tilde->~)

target_sources(airfx.electrohat_tilde
    PRIVATE
        airfx.electrohat_tilde.cpp)

target_include_directories(airfx.electrohat_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.electrohat_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
