set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestair_tilde) # output bundle: airfx.purestair~.mxo (_tilde->~)

target_sources(airfx.purestair_tilde
    PRIVATE
        airfx.purestair_tilde.cpp)

target_include_directories(airfx.purestair_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestair_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
