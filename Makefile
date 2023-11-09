# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++11 -IUnitTest++/src

# Список исходных файлов
SOURCES = modAlphaCipher.cpp main.cpp

# Генерация имен объектных файлов
OBJECTS = $(SOURCES:.cpp=.o)

# Имя исполняемого файла
EXECUTABLE = main

# Цель по умолчанию
all: $(EXECUTABLE)

# Компиляция исходных файлов
$(EXECUTABLE): $(OBJECTS)
    $(CXX) $(OBJECTS) -o $@

# Объектные файлы
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Цель для запуска тестов
test: $(EXECUTABLE)
    ./$(EXECUTABLE)

# Очистка временных файлов
clean:
    rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all test clean
