set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ynotnotch_tilde) # output bundle: airfx.ynotnotch~.mxo (_tilde->~)

target_sources(airfx.ynotnotch_tilde
    PRIVATE
        airfx.ynotnotch_tilde.cpp)

target_include_directories(airfx.ynotnotch_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ynotnotch_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
