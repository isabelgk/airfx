set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.console5darkch_tilde) # output bundle: airfx.console5darkch~.mxo (_tilde->~)

target_sources(airfx.console5darkch_tilde
    PRIVATE
        airfx.console5darkch_tilde.cpp)

target_include_directories(airfx.console5darkch_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.console5darkch_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
