# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11

# Исходные файлы
SOURCES = main.cpp solver.cpp
HEADERS = solver.h
EXECUTABLE = executor

# Значения h для анализа сходимости
#HS = 0.01 0.005 0.0025 0.001
#HS =  0.1 0.05 0.025 0.001
HS =   0.0001

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
