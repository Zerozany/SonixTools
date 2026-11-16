target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_17
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    SONIXTOOLS_BUILDING="${PROJECT_NAME}"
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
            PRIVATE
            "$<$<CONFIG:Debug>:/Z7>"
            "/utf-8"
            "/FS"
            "/bigobj"
            "$<$<CONFIG:Debug>:/Od>"
            "$<$<CONFIG:Release>:/Ox>"
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
            "-fdiagnostics-color=always" # 彩色输出诊断信息
            "-Wall" # 开启大部分警告
            "-Wextra" # 更多警告
            "$<$<CONFIG:Debug>:-O0>" # Debug 禁用优化
            "$<$<CONFIG:Release>:-O3>" # Release 最大优化
    )
endif()

if(ANDROID)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "-frtti"
    )
endif()
