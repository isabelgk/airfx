set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.chorusensemble_tilde) # output bundle: airfx.chorusensemble~.mxo (_tilde->~)

target_sources(airfx.chorusensemble_tilde
    PRIVATE
        airfx.chorusensemble_tilde.cpp)

target_include_directories(airfx.chorusensemble_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.chorusensemble_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
