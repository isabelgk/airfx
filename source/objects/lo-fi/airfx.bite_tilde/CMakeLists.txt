set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bite_tilde) # output bundle: airfx.bite~.mxo (_tilde->~)

target_sources(airfx.bite_tilde
    PRIVATE
        airfx.bite_tilde.cpp)

target_include_directories(airfx.bite_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bite_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
