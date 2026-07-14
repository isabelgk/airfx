set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.leftomono_tilde) # output bundle: airfx.leftomono~.mxo (_tilde->~)

target_sources(airfx.leftomono_tilde
    PRIVATE
        airfx.leftomono_tilde.cpp)

target_include_directories(airfx.leftomono_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.leftomono_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
