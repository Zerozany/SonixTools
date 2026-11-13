find_package(tomlplusplus CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(CMakeRC CONFIG REQUIRED)
find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp")

cmrc_add_resource_library(${PROJECT_NAME}-resources
    NAMESPACE ${PROJECT_NAME}R
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    tomlplusplus::tomlplusplus
    magic_enum::magic_enum
    ${PROJECT_NAME}-resources
)

if(ANDROID)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        log
    )
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${EXPRTK_INCLUDE_DIRS}
)
