if(NOT BasicTool_FOUND)
    include(BasicTool)
    message(STATUS ${PROJECT_NAME}.BasicTool_FOUND = ${BasicTool_FOUND} )
endif(NOT BasicTool_FOUND)


add_subdirectory(RayTracing)