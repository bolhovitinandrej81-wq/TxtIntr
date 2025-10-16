# Makefile для тригонометрического калькулятора

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGET = calculator
SOURCES = calculator.cpp

# Правило по умолчанию
all: $(TARGET)

# Сборка основной программы
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) -lm

# Отладочная сборка
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Быстрая сборка без оптимизаций
fast: CXXFLAGS = -std=c++11 -Wall -Wextra
fast: $(TARGET)

# Очистка
clean:
	rm -f $(TARGET)

# Установка в систему (требует прав суперпользователя)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Удаление из системы
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Запуск тестов
test: $(TARGET)
	@echo "=== Тестирование тригонометрического калькулятора ==="
	@echo "1. Тест синуса 30 градусов:"
	./$(TARGET) sin 30
	@echo ""
	@echo "2. Тест косинуса 60 градусов:"
	./$(TARGET) cos 60
	@echo ""
	@echo "3. Тест преобразования градусов в радианы:"
	./$(TARGET) deg2rad 180
	@echo ""
	@echo "4. Тест арксинуса 0.5:"
	./$(TARGET) asin 0.5
	@echo ""
	@echo "=== Тестирование завершено ==="

# Показать справку по использованию
help:
	@echo "Доступные цели:"
	@echo "  all       - сборка программы (по умолчанию)"
	@echo "  debug     - отладочная сборка"
	@echo "  fast      - быстрая сборка без оптимизаций"
	@echo "  clean     - удаление скомпилированных файлов"
	@echo "  install   - установка в систему"
	@echo "  uninstall - удаление из системы"
	@echo "  test      - запуск тестов"
	@echo "  help      - эта справка"
	@echo ""
	@echo "Примеры использования:"
	@echo "  ./calculator              # Интерактивный режим"
	@echo "  ./calculator sin 45       # Синус 45 градусов"
	@echo "  ./calculator cos 30 --радианы # Косинус 30 радиан"
	@echo "  ./calculator --помощь     # Показать справку"

.PHONY: all debug fast clean install uninstall test help
