set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ynotch_tilde) # output bundle: airfx.ynotch~.mxo (_tilde->~)

target_sources(airfx.ynotch_tilde
    PRIVATE
        airfx.ynotch_tilde.cpp)

target_include_directories(airfx.ynotch_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ynotch_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
