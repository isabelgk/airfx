set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kplate240_tilde) # output bundle: airfx.kplate240~.mxo (_tilde->~)

target_sources(airfx.kplate240_tilde
    PRIVATE
        airfx.kplate240_tilde.cpp)

target_include_directories(airfx.kplate240_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kplate240_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
