#include "Logging.h"

extern char last_sender[sender_length];

boolean Logging::Init(int level){
	_level = constrain(level, LOG_LEVEL_NOOUTPUT, LOG_LEVEL_VERBOSE);
//	_buf_size = 1000;
	_medium = SERIAL_MEDIUM;
	return true;
}

boolean Logging::Medium(int medium) {
	_medium = medium;
	return true;
}

void Logging::Error(const char* msg, ...){
	if (LOG_LEVEL_ERRORS <= _level) {
		//		print("ERROR: ", 0);
		print("ERROR: ", va_list());
		va_list args;
		va_start(args, msg);
		print(msg, args);
	}
}

void Logging::Error(String message, ...){
	if (LOG_LEVEL_ERRORS <= _level) {
		char msg[message.length() + 3];
		message.toCharArray(msg, message.length() + 1);
		strcat(msg, CR);
		print("ERROR: ", va_list());
		va_list args;
		va_start(args, msg);
		print(msg, args);
	}
}


void Logging::Info(const char* msg, ...){
	if (LOG_LEVEL_INFOS <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg, args);
	}
}

void Logging::Info(String message, ...){
	if (LOG_LEVEL_INFOS <= _level) {
		char msg[message.length() + 3];
		message.toCharArray(msg, message.length() + 1);
		strcat(msg, CR);
		va_list args;
		va_start(args, msg);
		print(msg, args);
	}
}

void Logging::Debug(const char* msg, ...){
	if (LOG_LEVEL_DEBUG <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg, args);
	}
}

void Logging::Debug(String message, ...){
	if (LOG_LEVEL_DEBUG <= _level) {
		char msg[message.length() + 3];
		message.toCharArray(msg, message.length() + 1);
		strcat(msg, CR);
		va_list args;
		va_start(args, msg);
		print(msg, args);
	}
}

void Logging::Verbose(const char* msg, ...){
	if (LOG_LEVEL_VERBOSE <= _level) {
		va_list args;
		va_start(args, msg);
		print(msg, args);
	}
}

void Logging::Verbose(String message, ...){
	if (LOG_LEVEL_VERBOSE <= _level) {
		char msg[message.length() + 3];
		message.toCharArray(msg, message.length() + 1);
		strcat(msg, CR);
		va_list args;
		va_start(args, msg);
		print(msg, args);
	}
}

//void Logging::print(String format, va_list args) {
//	char message[format.length() + 1];
//	format.toCharArray(message, format.length() + 1);
//	this->print(format, args);
//}

void Logging::print(const char *format, va_list args) {
	//
//	Stream stream = new Stream();
	// loop through format string

	uint8_t tx_buffer[2000];
	BufferSerial bs(tx_buffer, 2000);

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			if (*format == '\0') break;
			if (*format == '%') {
//				SerialUSB.print(*format);
				bs.print(*format);
				continue;
			}
			if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
//				SerialUSB.print(s);
				bs.print(s);
				continue;
			}
			if( *format == 'd' || *format == 'i') {
//				SerialUSB.print(va_arg( args, int ),DEC);
				bs.print(va_arg( args, int ),DEC);
				continue;
			}
			if( *format == 'x' ) {
//				SerialUSB.print(va_arg( args, int ),HEX);
				bs.print(va_arg( args, int ),HEX);
				continue;
			}
			if( *format == 'X' ) {
//				SerialUSB.print("0x");
				bs.print("0x");
//				SerialUSB.print(va_arg( args, int ),HEX);
				bs.print(va_arg( args, int ),HEX);
				continue;
			}
			if( *format == 'b' ) {
//				SerialUSB.print(va_arg( args, int ),BIN);
				bs.print(va_arg( args, int ),BIN);
				continue;
			}
			if( *format == 'B' ) {
//				SerialUSB.print("0b");
				bs.print("0b");
//				SerialUSB.print(va_arg( args, int ),BIN);
				bs.print(va_arg( args, int ),BIN);
				continue;
			}
			if( *format == 'l' ) {
//				SerialUSB.print(va_arg( args, long ),DEC);
				bs.print(va_arg( args, long ),DEC);
				continue;
			}

			if( *format == 'c' ) {
//				SerialUSB.print(va_arg( args, int ));
				bs.print(va_arg( args, int ));
				continue;
			}
			if( *format == 't' ) {
				if (va_arg( args, int ) == 1) {
//					SerialUSB.print("T");
					bs.print("T");
				}
				else {
//					SerialUSB.print("F");
					bs.print("F");
				}
				continue;
			}
			if( *format == 'T' ) {
				if (va_arg( args, int ) == 1) {
//					SerialUSB.print("true");
					bs.print("true");
				}
				else {
//					SerialUSB.print("false");
					bs.print("false");
				}
				continue;
			}
		}
//		SerialUSB.print(*format);
		bs.print(*format);
	}

	SerialUSB.print(bs);

	if (_medium == SMS_MEDIUM) {
		int temp_level = _level;
		_level = LOG_LEVEL_NOOUTPUT;
		gsmSMSsend(last_sender, bs);
		_level = temp_level;
	}
	if (_medium == TCP_MEDIUM) {
		int temp_level = _level;
		_level = LOG_LEVEL_NOOUTPUT;
		TCPsend(bs);
		_level = temp_level;
	}
}

Logging Log = Logging();








