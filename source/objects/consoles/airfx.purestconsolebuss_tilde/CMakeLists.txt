set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestconsolebuss_tilde) # output bundle: airfx.purestconsolebuss~.mxo (_tilde->~)

target_sources(airfx.purestconsolebuss_tilde
    PRIVATE
        airfx.purestconsolebuss_tilde.cpp)

target_include_directories(airfx.purestconsolebuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestconsolebuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
