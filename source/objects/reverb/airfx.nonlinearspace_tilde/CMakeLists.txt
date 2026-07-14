set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.nonlinearspace_tilde) # output bundle: airfx.nonlinearspace~.mxo (_tilde->~)

target_sources(airfx.nonlinearspace_tilde
    PRIVATE
        airfx.nonlinearspace_tilde.cpp)

target_include_directories(airfx.nonlinearspace_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.nonlinearspace_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
