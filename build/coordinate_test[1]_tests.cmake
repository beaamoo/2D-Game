add_test([=[CoordinateTest.Add]=]  /Users/bestricemossberg/Projects/C/2D-Game/build/coordinate_test [==[--gtest_filter=CoordinateTest.Add]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateTest.Add]=]  PROPERTIES WORKING_DIRECTORY /Users/bestricemossberg/Projects/C/2D-Game/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[CoordinateTest.Mul]=]  /Users/bestricemossberg/Projects/C/2D-Game/build/coordinate_test [==[--gtest_filter=CoordinateTest.Mul]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateTest.Mul]=]  PROPERTIES WORKING_DIRECTORY /Users/bestricemossberg/Projects/C/2D-Game/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
add_test([=[CoordinateTest.Move]=]  /Users/bestricemossberg/Projects/C/2D-Game/build/coordinate_test [==[--gtest_filter=CoordinateTest.Move]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateTest.Move]=]  PROPERTIES WORKING_DIRECTORY /Users/bestricemossberg/Projects/C/2D-Game/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  coordinate_test_TESTS CoordinateTest.Add CoordinateTest.Mul CoordinateTest.Move)
