set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.consolexbuss_tilde) # output bundle: airfx.consolexbuss~.mxo (_tilde->~)

target_sources(airfx.consolexbuss_tilde
    PRIVATE
        airfx.consolexbuss_tilde.cpp)

target_include_directories(airfx.consolexbuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.consolexbuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
