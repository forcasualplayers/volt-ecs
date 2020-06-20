add_executable(reflection_testlib test_reflection.cc)

target_compile_features(reflection_testlib PRIVATE cxx_std_17)
target_compile_options(reflection_testlib PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -pedantic -Werror>
)

if (LINUX)
target_compile_options(reflection_testlib PRIVATE
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Werror -stdlib=libc++>
)
elseif(WIN32)
target_compile_options(reflection_testlib PRIVATE
  $<$<CXX_COMPILER_ID:Clang>:/W4 /WX>
)
endif()

target_link_libraries(reflection_testlib volt_ecs)
target_link_libraries(reflection_testlib Catch2)

add_test(NAME reflection_test COMMAND reflection_testlib)