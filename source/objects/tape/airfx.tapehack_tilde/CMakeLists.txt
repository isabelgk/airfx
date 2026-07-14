set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tapehack_tilde) # output bundle: airfx.tapehack~.mxo (_tilde->~)

target_sources(airfx.tapehack_tilde
    PRIVATE
        airfx.tapehack_tilde.cpp)

target_include_directories(airfx.tapehack_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tapehack_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
