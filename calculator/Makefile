CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -lm
TARGET = calculator
SOURCES = calculator.cpp

# Установка русской локали
LOCALE = ru_RU.UTF-8

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	@LC_ALL=$(LOCALE) ./$(TARGET)

clean:
	rm -f $(TARGET) *.o

test: $(TARGET)
	@echo "=== Тестирование тригонометрического калькулятора ==="
	@echo "Запустите программу и протестируйте вручную:"
	@echo "  make run"
	@echo "Или используйте: ./calculator"

.PHONY: run clean test
