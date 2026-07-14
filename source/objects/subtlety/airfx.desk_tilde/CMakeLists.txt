set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.desk_tilde) # output bundle: airfx.desk~.mxo (_tilde->~)

target_sources(airfx.desk_tilde
    PRIVATE
        airfx.desk_tilde.cpp)

target_include_directories(airfx.desk_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.desk_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
