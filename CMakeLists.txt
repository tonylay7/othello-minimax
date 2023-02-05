# CMakeList.txt : CMake project for Othello, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Othello "Othello.cpp" "Othello.h" "BoardState.cpp" "BoardState.h" "MinimaxMoveChooser.cpp" "MinimaxMoveChooser.h" "TextDisplay.cpp" "TextDisplay.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Othello PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
