set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console8channelin_tilde) # output bundle: airfx.console8channelin~.mxo (_tilde->~)

target_sources(airfx.console8channelin_tilde
    PRIVATE
        airfx.console8channelin_tilde.cpp)

target_include_directories(airfx.console8channelin_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console8channelin_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
