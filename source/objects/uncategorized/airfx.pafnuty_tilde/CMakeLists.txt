set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pafnuty_tilde) # output bundle: airfx.pafnuty~.mxo (_tilde->~)

target_sources(airfx.pafnuty_tilde
    PRIVATE
        airfx.pafnuty_tilde.cpp)

target_include_directories(airfx.pafnuty_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pafnuty_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
