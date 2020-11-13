# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.18.4)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(json-populate NONE)

include(ExternalProject)
ExternalProject_Add(json-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent" "GIT_TAG" "v3.7.3"
                    SOURCE_DIR          "/Users/rayenayari/Desktop/BACHELOR/CSE201/trading-platform-pp/build/_deps/json-src"
                    BINARY_DIR          "/Users/rayenayari/Desktop/BACHELOR/CSE201/trading-platform-pp/build/_deps/json-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


