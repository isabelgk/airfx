set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.chimeydeluxe_tilde) # output bundle: airfx.chimeydeluxe~.mxo (_tilde->~)

target_sources(airfx.chimeydeluxe_tilde
    PRIVATE
        airfx.chimeydeluxe_tilde.cpp)

target_include_directories(airfx.chimeydeluxe_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.chimeydeluxe_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
