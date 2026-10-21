set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.punchydeluxe_tilde) # output bundle: airfx.punchydeluxe~.mxo (_tilde->~)

target_sources(airfx.punchydeluxe_tilde
    PRIVATE
        airfx.punchydeluxe_tilde.cpp)

target_include_directories(airfx.punchydeluxe_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.punchydeluxe_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
