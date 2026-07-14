set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.guitarconditioner_tilde) # output bundle: airfx.guitarconditioner~.mxo (_tilde->~)

target_sources(airfx.guitarconditioner_tilde
    PRIVATE
        airfx.guitarconditioner_tilde.cpp)

target_include_directories(airfx.guitarconditioner_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.guitarconditioner_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
