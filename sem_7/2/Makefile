# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11

# Исходные файлы
SOURCES = main.cpp solver.cpp
HEADERS = solver.h
EXECUTABLE = executor
OUT_DIR = ./solutions
IMG_DIR = ./images

HS =   0.000001

# Цель по умолчанию
all: run

# Правило для компиляции
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCES)

# Правило для запуска программы с разными h
run: $(EXECUTABLE)
	@for h in $(HS); do \
		echo "Запуск программы с h = $$h"; \
		./$(EXECUTABLE) $$h; \
	done
	

# Правило для очистки
clean:
	rm -f $(EXECUTABLE)
	rm -rf solutions

