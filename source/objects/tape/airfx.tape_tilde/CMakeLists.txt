set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tape_tilde) # output bundle: airfx.tape~.mxo (_tilde->~)

target_sources(airfx.tape_tilde
    PRIVATE
        airfx.tape_tilde.cpp)

target_include_directories(airfx.tape_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tape_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
