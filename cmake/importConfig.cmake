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
        "/utf-8"
        "/FS"
        "/bigobj"
    )
endif()

if(ANDROID)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "-frtti"
    )
endif()
