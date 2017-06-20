aux_source_directory(./world_server DIR_WORLD_SERVER)
aux_source_directory(./world_server_manager DIR_WORLD_SERVER_MANAGER)

include_directories(${LIB_DIR})
include_directories(${THIRDPARTY_DIR})
include_directories(./)

link_directories(
    ${PROJECT_SOURCE_DIR}/bin
)

set (LINK_LIB
    libsrv.a
    libcomm.a
    libbase.a
    
    libevent.a
    libevent_core.a
    libevent_extra.a
    libprotobuf.a
    libprotobuf-lite.a
    libprotoc.a
)

add_executable(world_server 
    main.cpp
    ${DIR_WORLD_SERVER}
    ${DIR_WORLD_SERVER_MANAGER}
    )
target_link_libraries(world_server 
    ${LINK_LIB}
    )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/world_server")