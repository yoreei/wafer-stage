export module logger;

import <iostream>;
import <fstream>;
import <mutex>;
import <filesystem>;
import <source_location>;
import <format>;
namespace fs = std::filesystem;

namespace logger {

    export enum LogLevel {
        INFO,
        DEBUG,
        TRACE,
    };

    export std::string str_from_LogLevel(LogLevel lvl) {
        switch (lvl) {
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::TRACE:
                return "TRACE";
        }
    }

    export class ILogger {
    public:
        virtual ~ILogger() = default;
        virtual void log(const LogLevel lvl,
                         const std::string_view txt,
                         const std::source_location& loc) = 0;
    };

    export class FileLogger : public ILogger {
    public:
        virtual ~FileLogger() override;
        virtual void log(const LogLevel lvl,
                         const std::string_view txt,
                         const std::source_location& loc) override;
        static FileLogger& get_instance();
    private:
        FileLogger() : FileLogger("./log.txt") {};
        FileLogger(const std::string& _path);
        FileLogger(const FileLogger&) = delete;
        FileLogger& operator=(const FileLogger&) = delete;

        fs::path m_path;
        std::ofstream m_file;
        std::mutex m_mtx;
    };

    FileLogger::~FileLogger() {
        if (m_file.is_open()) {
            m_file.close();
        }
    }

    FileLogger::FileLogger(const std::string& _path) : m_path(_path)
    {
        // TODO implement rotating log files
        m_file = {m_path, std::ios::app};

        if (!m_file.is_open()) {
            std::cerr << "Failed to open log file: " << m_path << std::endl;
        }
    }

    FileLogger& FileLogger::get_instance()
    {
        static FileLogger instance;
        return instance;
    }

    void FileLogger::log(const LogLevel lvl,
                         const std::string_view txt,
                         const std::source_location& loc)
    {
            std::lock_guard<std::mutex> lock(m_mtx);

            if (!m_file.is_open()) {
                std::cerr << "Log file not open!" << std::endl;
                return;
            }

            m_file << str_from_LogLevel(lvl) << ":"
                 << loc.file_name() << ':'
                 << loc.line() << ':'
                 // << loc.column() << ":"
                 << loc.function_name() << ":"
                 << txt << '\n';
            m_file.flush();
    }

    void _log(const LogLevel lvl,
              const std::string_view txt,
              const std::source_location& loc)
    {
        ILogger& logger = FileLogger::get_instance();
        logger.log(lvl, txt, loc);

    }
}

using namespace logger;

export inline void LOG_INFO(const std::string_view txt,
         const std::source_location loc =
               std::source_location::current())
{
    // TODO: integrate std::format
    _log(LogLevel::INFO, txt, loc);
}

export inline void LOG_DEBUG(const std::string_view txt,
         const std::source_location loc =
               std::source_location::current())
{
    _log(LogLevel::DEBUG, txt, loc);
}

export inline void LOG_TRACE(const std::string_view txt,
         const std::source_location loc =
               std::source_location::current())
{
    _log(LogLevel::TRACE, txt, loc);
}
