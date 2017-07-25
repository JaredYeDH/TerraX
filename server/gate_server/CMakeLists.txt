aux_source_directory(./gate_server DIR_GATE_SERVER)
aux_source_directory(./gate_account DIR_GATE_ACCOUNT)

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

add_executable(gate_server 
    main.cpp
    ${DIR_GATE_SERVER}
    ${DIR_GATE_ACCOUNT}
    )
target_link_libraries(gate_server 
    ${LINK_LIB}
    )

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/gate_server")