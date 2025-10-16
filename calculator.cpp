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
    std::cout << "Использование:\n";
    std::cout << "  ./calculator [операция] [значение] [--радианы]\n";
    std::cout << "  ./calculator --интерактивный\n\n";
    
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
    std::cout << "  rad2deg  - преобразовать радианы в градусы\n\n";
    
    std::cout << "Флаги:\n";
    std::cout << "  --радианы       - использовать радианы вместо градусов\n";
    std::cout << "  --интерактивный - запустить в интерактивном режиме\n";
    std::cout << "  --помощь        - показать эту справку\n\n";
    
    std::cout << "Примеры:\n";
    std::cout << "  ./calculator sin 45\n";
    std::cout << "  ./calculator cos 30 --радианы\n";
    std::cout << "  ./calculator asin 0.5\n";
    std::cout << "  ./calculator deg2rad 180\n";
    std::cout << "  ./calculator --интерактивный\n\n";
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

// Функция для выполнения операции в командной строке
void performCommandLineOperation(const std::string& operation, double value, bool useRadians) {
    try {
        currentMode = useRadians ? AngleMode::RADIANS : AngleMode::DEGREES;
        double result;
        std::string unit = (currentMode == AngleMode::DEGREES) ? "°" : " рад";
        
        if (operation == "sin") {
            result = calculateSin(value);
            std::cout << "sin(" << value << unit << ") = " << std::fixed << std::setprecision(6) << result << std::endl;
        }
        else if (operation == "cos") {
            result = calculateCos(value);
            std::cout << "cos(" << value << unit << ") = " << std::fixed << std::setprecision(6) << result << std::endl;
        }
        else if (operation == "tan") {
            result = calculateTan(value);
            std::cout << "tan(" << value << unit << ") = " << std::fixed << std::setprecision(6) << result << std::endl;
        }
        else if (operation == "ctg") {
            result = calculateCtg(value);
            std::cout << "ctg(" << value << unit << ") = " << std::fixed << std::setprecision(6) << result << std::endl;
        }
        else if (operation == "asin") {
            result = calculateAsin(value);
            std::cout << "asin(" << value << ") = " << std::fixed << std::setprecision(6) << result << unit << std::endl;
        }
        else if (operation == "acos") {
            result = calculateAcos(value);
            std::cout << "acos(" << value << ") = " << std::fixed << std::setprecision(6) << result << unit << std::endl;
        }
        else if (operation == "atan") {
            result = calculateAtan(value);
            std::cout << "atan(" << value << ") = " << std::fixed << std::setprecision(6) << result << unit << std::endl;
        }
        else if (operation == "actg") {
            result = calculateActg(value);
            std::cout << "actg(" << value << ") = " << std::fixed << std::setprecision(6) << result << unit << std::endl;
        }
        else if (operation == "deg2rad") {
            result = degreesToRadians(value);
            std::cout << value << "° = " << std::fixed << std::setprecision(6) << result << " рад" << std::endl;
        }
        else if (operation == "rad2deg") {
            result = radiansToDegrees(value);
            std::cout << value << " рад = " << std::fixed << std::setprecision(6) << result << "°" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        std::exit(1);
    }
}

// Функция для выполнения операции в интерактивном режиме
void performInteractiveOperation(const std::string& operation) {
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

// Функция для вывода справки интерактивного режима
void printInteractiveHelp() {
    std::cout << "\n=== ИНТЕРАКТИВНЫЙ РЕЖИМ ===\n\n";
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

// Главный цикл интерактивного режима
void runInteractiveMode() {
    std::string command;
    
    std::cout << "=== ТРИГОНОМЕТРИЧЕСКИЙ КАЛЬКУЛЯТОР (Интерактивный режим) ===\n";
    std::cout << "Режим работы: " << (currentMode == AngleMode::DEGREES ? "ГРАДУСЫ" : "РАДИАНЫ") << "\n\n";
    
    printInteractiveHelp();
    
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
            printInteractiveHelp();
        }
        else if (command == "mode" || command == "режим") {
            switchMode();
        }
        else if (command == "sin" || command == "cos" || command == "tan" || command == "ctg" ||
                 command == "asin" || command == "acos" || command == "atan" || command == "actg" ||
                 command == "deg2rad" || command == "rad2deg") {
            performInteractiveOperation(command);
        }
        else {
            std::cout << "Неизвестная команда. Введите 'help' для просмотра доступных операций.\n";
        }
    }
}

// Обработка аргументов командной строки
void handleCommandLine(int argc, char* argv[]) {
    if (argc == 1) {
        // Если нет аргументов, запускаем интерактивный режим
        runInteractiveMode();
        return;
    }
    
    std::vector<std::string> args(argv + 1, argv + argc);
    bool useRadians = false;
    bool interactiveMode = false;
    std::string operation;
    double value = 0.0;
    
    // Парсинг аргументов
    for (const auto& arg : args) {
        if (arg == "--радианы" || arg == "--radians") {
            useRadians = true;
        }
        else if (arg == "--интерактивный" || arg == "--interactive") {
            interactiveMode = true;
        }
        else if (arg == "--помощь" || arg == "--help") {
            printHelp();
            return;
        }
        else if (operation.empty() && 
                 (arg == "sin" || arg == "cos" || arg == "tan" || arg == "ctg" ||
                  arg == "asin" || arg == "acos" || arg == "atan" || arg == "actg" ||
                  arg == "deg2rad" || arg == "rad2deg")) {
            operation = arg;
        }
        else if (value == 0.0) {
            try {
                value = std::stod(arg);
            } catch (const std::exception& e) {
                // Игнорируем ошибки преобразования, это может быть неизвестный флаг
            }
        }
    }
    
    if (interactiveMode) {
        runInteractiveMode();
    }
    else if (!operation.empty() && value != 0.0) {
        performCommandLineOperation(operation, value, useRadians);
    }
    else {
        std::cout << "Неверные аргументы командной строки.\n";
        printHelp();
        std::exit(1);
    }
}

int main(int argc, char* argv[]) {
    try {
        handleCommandLine(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Произошла непредвиденная ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
