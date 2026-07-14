set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console8channelhype_tilde) # output bundle: airfx.console8channelhype~.mxo (_tilde->~)

target_sources(airfx.console8channelhype_tilde
    PRIVATE
        airfx.console8channelhype_tilde.cpp)

target_include_directories(airfx.console8channelhype_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console8channelhype_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
