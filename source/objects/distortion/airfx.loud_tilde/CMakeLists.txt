set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.loud_tilde) # output bundle: airfx.loud~.mxo (_tilde->~)

target_sources(airfx.loud_tilde
    PRIVATE
        airfx.loud_tilde.cpp)

target_include_directories(airfx.loud_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.loud_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
