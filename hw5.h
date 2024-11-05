#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <vector>
#include <initializer_list>

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

	void logTime(std::string message, LogLevels logLevel) const {
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

	template <typename Container>
	void logContainer(const Container& container) const;

	template <typename T>
	void logContainer(const std::initializer_list<T>& ilist) const;

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