set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.righteous4_tilde) # output bundle: airfx.righteous4~.mxo (_tilde->~)

target_sources(airfx.righteous4_tilde
    PRIVATE
        airfx.righteous4_tilde.cpp)

target_include_directories(airfx.righteous4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.righteous4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
