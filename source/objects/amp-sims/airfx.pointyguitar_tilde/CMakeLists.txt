set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pointyguitar_tilde) # output bundle: airfx.pointyguitar~.mxo (_tilde->~)

target_sources(airfx.pointyguitar_tilde
    PRIVATE
        airfx.pointyguitar_tilde.cpp)

target_include_directories(airfx.pointyguitar_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pointyguitar_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
