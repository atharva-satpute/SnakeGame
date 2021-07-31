# for linux
ifeq ($(TARGET),linux)
snakeGame: SnakeGame.cpp kbhit.cpp
		g++ SnakeGame.cpp kbhit.cpp -o snakeGame -I .
endif

# for windows
ifeq ($(TARGET),windows)
snakeGame: SnakeGame.cpp kbhit.cpp
		g++ SnakeGame.cpp kbhit.cpp -o snakeGame.exe -I .
endif