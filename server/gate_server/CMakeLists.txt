aux_source_directory(./gate_server DIR_GATE_SERVER)

include_directories(${LIB_DIR})
include_directories(${THIRDPARTY_DIR})

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

add_executable(gate_server 
    main.cpp
    ${DIR_GATE_SERVER}
    )
target_link_libraries(gate_server 
    ${LINK_LIB}
    )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/gate_server")