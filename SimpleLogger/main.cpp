
#include "SimpleLoggerInt.h"
#include <fstream>

int main(){
	Appender* appender1 = new Appender(DEBUG, "log1.log");
	Logger* logger = new Logger("logger");
	logger->AddAppender("appender1", appender1);
	logger->Start();

	logger->Logging(DEBUG, "second log");
	

	logger->Shutdown();

	return 0;
}