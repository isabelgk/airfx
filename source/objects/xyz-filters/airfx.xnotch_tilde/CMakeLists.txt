set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.xnotch_tilde) # output bundle: airfx.xnotch~.mxo (_tilde->~)

target_sources(airfx.xnotch_tilde
    PRIVATE
        airfx.xnotch_tilde.cpp)

target_include_directories(airfx.xnotch_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.xnotch_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
