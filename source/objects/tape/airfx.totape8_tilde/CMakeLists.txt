set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.totape8_tilde) # output bundle: airfx.totape8~.mxo (_tilde->~)

target_sources(airfx.totape8_tilde
    PRIVATE
        airfx.totape8_tilde.cpp)

target_include_directories(airfx.totape8_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.totape8_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
