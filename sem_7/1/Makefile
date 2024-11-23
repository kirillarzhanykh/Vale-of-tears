# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Файлы
SRC_DIR = .
BIN_DIR = ./bin
OUT_DIR = ./output
IMG_DIR = ./images

# Исходные файлы
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/solver.cpp
TARGET = $(BIN_DIR)/solver

# Значения h, для которых будем строить графики и замерять время
HS = 0.00016 0.00008 0.00004 0.00002 0.00001
# Файл для записи времени выполнения
TIMING_FILE = timing_results.txt

# Цель по умолчанию
all: run_all_plots

# Компиляция программы
$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Запуск программы с разными значениями h, построение графиков и запись времени
run_all_plots: $(TARGET)
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(IMG_DIR)
	@echo "h и время выполнения" > $(TIMING_FILE)
	@for h in $(HS); do \
		echo "Запуск с шагом $$h ..."; \
		$(TARGET) $$h $(OUT_DIR)/solution_$$h.txt; \
		python3 plot_solution.py $(OUT_DIR)/solution_$$h.txt $(IMG_DIR)/plot_$$h.png $$h; \
	done
	@echo "Графики построены и сохранены в $(IMG_DIR)"
	python3 plot_timing.py $(TIMING_FILE) $(IMG_DIR)/timing_plot.png
	python3 plot_errors.py $(OUT_DIR)



# Очистка всех сгенерированных файлов
clean:
	rm -rf $(BIN_DIR) $(OUT_DIR) $(IMG_DIR) $(TIMING_FILE)