set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.everyslew_tilde) # output bundle: airfx.everyslew~.mxo (_tilde->~)

target_sources(airfx.everyslew_tilde
    PRIVATE
        airfx.everyslew_tilde.cpp)

target_include_directories(airfx.everyslew_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.everyslew_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
