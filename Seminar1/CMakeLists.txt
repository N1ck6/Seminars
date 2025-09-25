cmake_minimum_required(VERSION 3.14)
project(SortingTests)

# Устанавливаем политики CMake для избежания предупреждений
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

# Способ 1: Используем прямой URL для загрузки
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    URL_HASH SHA256=ff7a82736e158c077e76188230e2ca2d7b3201197a46c7b34d3a4af5c3f7c9b6
)

FetchContent_MakeAvailable(googletest)

# Или Способ 2: Альтернативный источник (если первый не работает)
# FetchContent_Declare(
#     googletest
#     URL https://github.com/google/googletest/archive/refs/heads/main.zip
# )

# Или Способ 3: Используем git (если есть доступ)
# FetchContent_Declare(
#     googletest
#     GIT_REPOSITORY https://github.com/google/googletest.git
#     GIT_TAG release-1.13.0
# )

# Библиотека сортировки для векторов
add_library(bubble_sort_vector sorting/src/bubble_sort_vector.cpp)
target_include_directories(bubble_sort_vector PUBLIC sorting/include)

# Тесты для векторов
add_executable(test_bubble_sort_vector tests/test_bubble_sort_vector.cpp)
target_link_libraries(test_bubble_sort_vector bubble_sort_vector gtest_main)
target_include_directories(test_bubble_sort_vector PRIVATE sorting/include)

enable_testing()
add_test(NAME BubbleSortVectorTest COMMAND test_bubble_sort_vector)