set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tube_tilde) # output bundle: airfx.tube~.mxo (_tilde->~)

target_sources(airfx.tube_tilde
    PRIVATE
        airfx.tube_tilde.cpp)

target_include_directories(airfx.tube_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tube_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
