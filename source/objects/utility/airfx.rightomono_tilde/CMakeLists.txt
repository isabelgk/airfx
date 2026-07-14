set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.rightomono_tilde) # output bundle: airfx.rightomono~.mxo (_tilde->~)

target_sources(airfx.rightomono_tilde
    PRIVATE
        airfx.rightomono_tilde.cpp)

target_include_directories(airfx.rightomono_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.rightomono_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
