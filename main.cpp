#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <vector>
#pragma warning(disable: 4996)

enum class LogLevels {
	info = 0,
	warning = 1,
	error = 2,
};

class Logger {
private:
	std::string getCurrentTime() const {
		auto now = std::chrono::system_clock::now();
		auto time_t_now = std::chrono::system_clock::to_time_t(now);
		std::tm* tm_now = std::localtime(&time_t_now);

		std::ostringstream oss;
		oss << std::put_time(tm_now, "%H:%M:%S");
		return oss.str();
	}

	Logger() = default;
public:
	static Logger& getInstance() {
		static Logger logger;
		return logger;
	}

	void log(std::string message, LogLevels logLevel) const {
		std::ofstream logFile("log.txt", std::ios::app);
		if (logFile.is_open()) {
			switch (logLevel) {
			case LogLevels::info:
				logFile << "Info: " << getCurrentTime() << " - " << message << std::endl;
				break;
			case LogLevels::warning:
				logFile << "Warning: " << getCurrentTime() << " - " << message << std::endl;
				break;
			case LogLevels::error:
				logFile << "Error: " << getCurrentTime() << " - " << message << std::endl;
				break;
			default:
				std::cerr << "Wrong LogLevel catched :(" << std::endl;
			}
		}
		else {
			std::cerr << "File opening is unsuccesful :(" << std::endl;
		}
	}

	Logger(const Logger&) = delete;
	Logger operator=(const Logger&) = delete;
	~Logger() = default;
};

class ConfigManager {
private:
	struct Config {
		std::string key;
		std::string value;

		Config(std::string key, std::string value) {
			this->key = key;
			this->value = value;
		}
	};

	std::vector<Config> config;
	ConfigManager() = default;
public:
	void setConfig(const std::string key, const std::string value) {
		config.push_back(Config(key, value));
	}

	std::string getConfig(const std::string key) {
		for (int i = 0; i < config.size(); i++) {
			if (key == config[i].key) {
				return config[i].value;
			}
		}
		throw std::runtime_error("Key is not found");
	}

	ConfigManager(const ConfigManager&) = delete;
	ConfigManager operator=(const ConfigManager&) = delete;
	~ConfigManager() = default;
	static ConfigManager& getInstance() {
		static ConfigManager configManager;
		return configManager;
	}
};

int main() {
	Logger::getInstance().log("asd", LogLevels::info);
	Logger::getInstance().log("fgh", LogLevels::warning);
	ConfigManager::getInstance().setConfig("1", "qwerty");
	try {
		std::cout << ConfigManager::getInstance().getConfig("1") << std::endl;
		std::cout << ConfigManager::getInstance().getConfig("12") << std::endl;
	}
	catch (std::runtime_error error) {
		std::cerr << error.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error" << std::endl;
	}

	return 0;
}