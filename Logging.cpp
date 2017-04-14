#include "Logging.h"

void Logging::Init(int level, long baud){
	_level = constrain(level,LOG_LEVEL_NOOUTPUT,LOG_LEVEL_VERBOSE);
	_baud = baud;
	//    SerialUSB.begin(_baud);
}

void Logging::Error(char* msg, ...){
	if (LOG_LEVEL_ERRORS <= _level) {
		//		print("ERROR: ", 0);
		print("ERROR: ", va_list());
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}


void Logging::Info(char* msg, ...){
	if (LOG_LEVEL_INFOS <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}

void Logging::Debug(char* msg, ...){
	if (LOG_LEVEL_DEBUG <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}


void Logging::Verbose(char* msg, ...){
	if (LOG_LEVEL_VERBOSE <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg,args);
	}
}



void Logging::print(const char *format, va_list args) {
	//
	// loop through format string
	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			if (*format == '\0') break;
			if (*format == '%') {
				SerialUSB.print(*format);
				continue;
			}
			if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				SerialUSB.print(s);
				continue;
			}
			if( *format == 'd' || *format == 'i') {
				SerialUSB.print(va_arg( args, int ),DEC);
				continue;
			}
			if( *format == 'x' ) {
				SerialUSB.print(va_arg( args, int ),HEX);
				continue;
			}
			if( *format == 'X' ) {
				SerialUSB.print("0x");
				SerialUSB.print(va_arg( args, int ),HEX);
				continue;
			}
			if( *format == 'b' ) {
				SerialUSB.print(va_arg( args, int ),BIN);
				continue;
			}
			if( *format == 'B' ) {
				SerialUSB.print("0b");
				SerialUSB.print(va_arg( args, int ),BIN);
				continue;
			}
			if( *format == 'l' ) {
				SerialUSB.print(va_arg( args, long ),DEC);
				continue;
			}

			if( *format == 'c' ) {
				SerialUSB.print(va_arg( args, int ));
				continue;
			}
			if( *format == 't' ) {
				if (va_arg( args, int ) == 1) {
					SerialUSB.print("T");
				}
				else {
					SerialUSB.print("F");
				}
				continue;
			}
			if( *format == 'T' ) {
				if (va_arg( args, int ) == 1) {
					SerialUSB.print("true");
				}
				else {
					SerialUSB.print("false");
				}
				continue;
			}

		}
		SerialUSB.print(*format);
	}
}

Logging Log = Logging();








