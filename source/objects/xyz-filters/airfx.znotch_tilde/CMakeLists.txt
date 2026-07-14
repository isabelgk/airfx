set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.znotch_tilde) # output bundle: airfx.znotch~.mxo (_tilde->~)

target_sources(airfx.znotch_tilde
    PRIVATE
        airfx.znotch_tilde.cpp)

target_include_directories(airfx.znotch_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.znotch_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
