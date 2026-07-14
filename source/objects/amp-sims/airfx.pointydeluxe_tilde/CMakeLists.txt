set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pointydeluxe_tilde) # output bundle: airfx.pointydeluxe~.mxo (_tilde->~)

target_sources(airfx.pointydeluxe_tilde
    PRIVATE
        airfx.pointydeluxe_tilde.cpp)

target_include_directories(airfx.pointydeluxe_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pointydeluxe_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
