set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.precious_tilde) # output bundle: airfx.precious~.mxo (_tilde->~)

target_sources(airfx.precious_tilde
    PRIVATE
        airfx.precious_tilde.cpp)

target_include_directories(airfx.precious_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.precious_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
