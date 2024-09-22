# CMakeLists.txt inside "Week1- Value Category"

# Collect all .cpp and .hpp files in this folder
file(GLOB_RECURSE LESSONS_SOURCE "*.cpp" "*.hpp")

# Expose the variable WEEK1_SOURCES to the parent scope
set(LESSONS_SOURCE ${LESSONS_SOURCE} PARENT_SCOPE)