#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <locale>
#include <stdexcept>
#include <limits>
#include <cmath>

// Установка русской локали
class RussianLocale {
public:
    RussianLocale() {
        try {
            std::locale::global(std::locale("ru_RU.UTF-8"));
        }
        catch (const std::exception& e) {
            std::cout << "Предупреждение: Не удалось установить русскую локаль. Используется системная локаль." << std::endl;
        }
    }
};

// Глобальный объект для установки локали при запуске
RussianLocale russianLocale;

// Перечисление для режимов работы (градусы/радианы)
enum class AngleMode { DEGREES, RADIANS };

AngleMode currentMode = AngleMode::DEGREES;

// Функция для преобразования градусов в радианы
double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Функция для преобразования радианов в градусы
double radiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
}

// Функция для вывода справки
void printHelp() {
    std::cout << "\n=== ТРИГОНОМЕТРИЧЕСКИЙ КАЛЬКУЛЯТОР ===\n\n";
    std::cout << "Доступные операции:\n";
    std::cout << "  sin      - синус угла\n";
    std::cout << "  cos      - косинус угла\n";
    std::cout << "  tan      - тангенс угла\n";
    std::cout << "  ctg      - котангенс угла\n";
    std::cout << "  asin     - арксинус числа\n";
    std::cout << "  acos     - арккосинус числа\n";
    std::cout << "  atan     - арктангенс числа\n";
    std::cout << "  actg     - арккотангенс числа\n";
    std::cout << "  deg2rad  - преобразовать градусы в радианы\n";
    std::cout << "  rad2deg  - преобразовать радианы в градусы\n";
    std::cout << "  mode     - переключить режим (градусы/радианы)\n";
    std::cout << "  help     - показать эту справку\n";
    std::cout << "  exit     - выйти из программы\n\n";
    std::cout << "Текущий режим: " << (currentMode == AngleMode::DEGREES ? "ГРАДУСЫ" : "РАДИАНЫ") << "\n\n";
}

// Функция для очистки буфера ввода
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Функция для ввода числа от пользователя
double inputNumber(const std::string& prompt) {
    double number;
    while (true) {
        std::cout << prompt;
        std::cin >> number;
        
        if (std::cin.fail()) {
            std::cout << "Ошибка: Пожалуйста, введите корректное число.\n";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            break;
        }
    }
    return number;
}

// Функция для переключения режима
void switchMode() {
    if (currentMode == AngleMode::DEGREES) {
        currentMode = AngleMode::RADIANS;
        std::cout << "Режим изменен на: РАДИАНЫ\n";
    } else {
        currentMode = AngleMode::DEGREES;
        std::cout << "Режим изменен на: ГРАДУСЫ\n";
    }
}

// Тригонометрические функции с учетом текущего режима
double calculateSin(double angle) {
    if (currentMode == AngleMode::DEGREES) {
        angle = degreesToRadians(angle);
    }
    return std::sin(angle);
}

double calculateCos(double angle) {
    if (currentMode == AngleMode::DEGREES) {
        angle = degreesToRadians(angle);
    }
    return std::cos(angle);
}

double calculateTan(double angle) {
    if (currentMode == AngleMode::DEGREES) {
        angle = degreesToRadians(angle);
    }
    return std::tan(angle);
}

double calculateCtg(double angle) {
    double tanValue = calculateTan(angle);
    if (tanValue == 0) {
        throw std::domain_error("Котангенс не определен для этого угла");
    }
    return 1.0 / tanValue;
}

// Обратные тригонометрические функции
double calculateAsin(double value) {
    if (value < -1.0 || value > 1.0) {
        throw std::domain_error("Арксинус определен только для значений от -1 до 1");
    }
    double result = std::asin(value);
    if (currentMode == AngleMode::DEGREES) {
        result = radiansToDegrees(result);
    }
    return result;
}

double calculateAcos(double value) {
    if (value < -1.0 || value > 1.0) {
        throw std::domain_error("Арккосинус определен только для значений от -1 до 1");
    }
    double result = std::acos(value);
    if (currentMode == AngleMode::DEGREES) {
        result = radiansToDegrees(result);
    }
    return result;
}

double calculateAtan(double value) {
    double result = std::atan(value);
    if (currentMode == AngleMode::DEGREES) {
        result = radiansToDegrees(result);
    }
    return result;
}

double calculateActg(double value) {
    if (value == 0) {
        throw std::domain_error("Арккотангенс не определен для нуля");
    }
    double result = std::atan(1.0 / value);
    if (currentMode == AngleMode::DEGREES) {
        result = radiansToDegrees(result);
    }
    return result;
}

// Функция для выполнения операции
void performOperation(const std::string& operation) {
    try {
        double input, result;
        std::string unit = (currentMode == AngleMode::DEGREES) ? "°" : " рад";
        
        if (operation == "sin") {
            input = inputNumber("Введите угол: ");
            result = calculateSin(input);
            std::cout << "sin(" << input << unit << ") = " << std::fixed << std::setprecision(6) << result << "\n\n";
        }
        else if (operation == "cos") {
            input = inputNumber("Введите угол: ");
            result = calculateCos(input);
            std::cout << "cos(" << input << unit << ") = " << std::fixed << std::setprecision(6) << result << "\n\n";
        }
        else if (operation == "tan") {
            input = inputNumber("Введите угол: ");
            result = calculateTan(input);
            std::cout << "tan(" << input << unit << ") = " << std::fixed << std::setprecision(6) << result << "\n\n";
        }
        else if (operation == "ctg") {
            input = inputNumber("Введите угол: ");
            result = calculateCtg(input);
            std::cout << "ctg(" << input << unit << ") = " << std::fixed << std::setprecision(6) << result << "\n\n";
        }
        else if (operation == "asin") {
            input = inputNumber("Введите значение от -1 до 1: ");
            result = calculateAsin(input);
            std::cout << "asin(" << input << ") = " << std::fixed << std::setprecision(6) << result << unit << "\n\n";
        }
        else if (operation == "acos") {
            input = inputNumber("Введите значение от -1 до 1: ");
            result = calculateAcos(input);
            std::cout << "acos(" << input << ") = " << std::fixed << std::setprecision(6) << result << unit << "\n\n";
        }
        else if (operation == "atan") {
            input = inputNumber("Введите значение: ");
            result = calculateAtan(input);
            std::cout << "atan(" << input << ") = " << std::fixed << std::setprecision(6) << result << unit << "\n\n";
        }
        else if (operation == "actg") {
            input = inputNumber("Введите значение: ");
            result = calculateActg(input);
            std::cout << "actg(" << input << ") = " << std::fixed << std::setprecision(6) << result << unit << "\n\n";
        }
        else if (operation == "deg2rad") {
            input = inputNumber("Введите градусы: ");
            result = degreesToRadians(input);
            std::cout << input << "° = " << std::fixed << std::setprecision(6) << result << " рад\n\n";
        }
        else if (operation == "rad2deg") {
            input = inputNumber("Введите радианы: ");
            result = radiansToDegrees(input);
            std::cout << input << " рад = " << std::fixed << std::setprecision(6) << result << "°\n\n";
        }
        
        // Сброс формата вывода
        std::cout.unsetf(std::ios_base::floatfield);
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n\n";
    }
}

// Главный цикл программы
void runCalculator() {
    std::string command;
    
    std::cout << "=== ТРИГОНОМЕТРИЧЕСКИЙ КАЛЬКУЛЯТОР ===\n";
    std::cout << "Режим работы: " << (currentMode == AngleMode::DEGREES ? "ГРАДУСЫ" : "РАДИАНЫ") << "\n\n";
    
    printHelp();
    
    while (true) {
        std::cout << "Введите операцию: ";
        std::getline(std::cin, command);
        
        // Преобразование в нижний регистр для удобства
        for (char& c : command) {
            c = std::tolower(c);
        }
        
        if (command == "exit" || command == "quit" || command == "выход") {
            std::cout << "Спасибо за использование тригонометрического калькулятора! До свидания!\n";
            break;
        }
        else if (command == "help" || command == "справка") {
            printHelp();
        }
        else if (command == "mode" || command == "режим") {
            switchMode();
        }
        else if (command == "sin" || command == "cos" || command == "tan" || command == "ctg" ||
                 command == "asin" || command == "acos" || command == "atan" || command == "actg" ||
                 command == "deg2rad" || command == "rad2deg") {
            performOperation(command);
        }
        else {
            std::cout << "Неизвестная команда. Введите 'help' для просмотра доступных операций.\n";
        }
    }
}

int main() {
    try {
        runCalculator();
    } catch (const std::exception& e) {
        std::cerr << "Произошла непредвиденная ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
