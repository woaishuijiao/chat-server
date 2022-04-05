#include <iostream>
#include "../log.h"
#include <time.h>
#include <thread>
#include "../util.h"

int main(int argc, char* argv[]) {
	jiong::Logger::ptr logger(new jiong::Logger);
	logger->addAppender(jiong::LogAppender::ptr(new jiong::StdoutLogAppender));

	jiong::LogAppender::ptr file_appender(new jiong::FileLogAppender("./log.txt"));
	jiong::LogFormatter::ptr fmt(new jiong::LogFormatter("%d%T%p%T%m%n"));
	file_appender->setFormatter(fmt);
	file_appender->setLevel(jiong::LogLevel::ERROR);

	logger->addAppender(file_appender);

//	jiong::LogEvent::ptr event(new jiong::LogEvent(logger, jiong::LogLevel::INFO, __FILE__, __LINE__, 0, jiong::GetThreadId(), jiong::GetFiberId(), time(0)));
//	event->getSS() << "hello jiong log";
//
//	logger->log(jiong::LogLevel::DEBUG, event);

	JIONG_LOG_INFO(logger) << "test macro";
	JIONG_LOG_ERROR(logger) << "test macro error";

	JIONG_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

	auto l = jiong::LoggerMgr::GetInstance()->getLogger("xx");
	JIONG_LOG_INFO(l) << "xxx";
	return 0;
}
