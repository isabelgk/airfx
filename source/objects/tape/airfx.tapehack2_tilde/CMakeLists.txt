set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tapehack2_tilde) # output bundle: airfx.tapehack2~.mxo (_tilde->~)

target_sources(airfx.tapehack2_tilde
    PRIVATE
        airfx.tapehack2_tilde.cpp)

target_include_directories(airfx.tapehack2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tapehack2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
