#include "Log.h"

void Log::Initialize(void* params) {
	Log::Information("Initialized LogManager App", "Log.h", 17);
	timer->in(LOG_FLUSH_TIMER, FlushTimer, this);
};

void Log::Run() {
start:;
	delay(1000);
	if (Log::GetBufferIndex() >= Log::GetFlushLimit()) {
		IgnoreNextTimerCall = 1;
		goto doflush;
	}
	if (FlushLogTimer) {
		FlushLogTimer = 0;
		if (IgnoreNextTimerCall) {
			IgnoreNextTimerCall = 0;
			goto start;
		}
		goto doflush;
	};
	goto start;
doflush:;
	Log::Flush();
};

bool Log::FlushTimer(void* opaque) {
	static_cast<Log*>(opaque)->FlushLogTimer = 1;
	timer->in(LOG_FLUSH_TIMER, FlushTimer, opaque);
};

void Log::Flush(){
	WriteMessageSync->Lock();
	ArraySequence<Message>*placeholder = WorkingBuffer; //Store pointer to EMPTY Working Buffer
	WorkingBuffer = MessageBuffer; //Store pointer from used MessageBuffer in WorkingBuffer
	MessageBuffer = placeholder; //Placing EMPTY working buffer in MessageBuffer
	WriteMessageSync->Unlock();

	//Divide task into several sweeps
	int div = LOG_MESSAGE_BUFFER_SIZE / LOG_FLUSH_TASK_DIVIDE;
	Message* msg;
	for (int c = 0, i = 0, divi = 0; i < WorkingBuffer->Index; i++) {
		if (divi >= div && c < LOG_FLUSH_TASK_DIVIDE + 1) {
			c++;
			divi = 0;
			delay(100);
		}
		msg = WorkingBuffer->GetPointer(i);
		divi++;
		//Output the logs somewhere...
		if (Serial) {
			OutputSerial(msg, i);
		}
	}
	WorkingBuffer->Index = 0;
}

void Log::OutputSerial(Message* msg, int i) {
#define P Serial.print
#define PL Serial.println
#ifdef DEBUG
	P("Buffer["); P(i); PL(']');
#endif
	P(msg->IssueDate); P(" ["); P(Log::LevelString(msg->Level)); P("] ");
	P(msg->Filename); P("@"); P(msg->Linenumber); P(" :: "); P(msg->MessageDat);
#ifdef LOG_RAM
	P(" | FreeMem: "); P(MemoryUnits(msg->FreeMem, 2)); P("MB");
#endif
	PL();
#undef P
#undef PL
}

void Log::ForceFlush() {
	WriteMessageSync->Lock();
	Message* msg;
	if (Serial) {
		Serial.println("Force Flushing buffers...");
		Serial.println("Working Buffer flush");
	}
	for (int i = 0; i < WorkingBuffer->Index; i++) {
		msg = WorkingBuffer->GetPointer(i);
		//Output the logs somewhere...
		if (Serial) {
			OutputSerial(msg, i);
		}
	}
	WorkingBuffer->Index = 0;

	if (Serial) {
		Serial.println("Message Buffer flush");
	}
	for (int i = 0; i < MessageBuffer->Index; i++) {
		msg = MessageBuffer->GetPointer(i);
		//Output the logs somewhere...
		if (Serial) {
			OutputSerial(msg, i);
		}
	}
	MessageBuffer->Index = 0;
	WriteMessageSync->Unlock();
}

void Log::makemsg(String dat, const char* filename, int16_t linenumber, Log::LogLevel lv) {
	WriteMessageSync->Lock();
	Message* msg = MessageBuffer->Next();
	WriteMessageSync->Unlock();
	msg->Filename = filename;
	msg->Linenumber = linenumber;
	msg->MessageDat = dat;
	msg->Level = lv;
	msg->IssueDate = ttgo->rtc->formatDateTime();
#ifdef DEBUG
	msg->FreeMem = Debug::FreeRam();
#endif
}

const char* Log::LevelString(Log::LogLevel lv) {
	const const char* strs[]{
		"FTL",
		"ERR",
		"WRN",
		"INF",
		"DBG",
		"VRB",
	};
	return strs[static_cast<int>(lv)];
}

int Log::GetBufferIndex() {
	return WorkingBuffer->Index;
}

int Log::GetFlushLimit() {
	return Log::FlushLimit;
}

bool Log::GetIsFlushing() {
	return Log::_IsFlushing;
}

void Log::Fatal(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
	makemsg(dat, filename, defaultlinenumber, LogLevel::Fatal);
};

void Log::Error(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
	if (Level < LogLevel::Error) {
		return;
	}
	makemsg(dat, filename, defaultlinenumber, LogLevel::Error);
};

void Log::Warning(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
	if (Level < LogLevel::Warning) {
		return;
	}
	makemsg(dat, filename, defaultlinenumber, LogLevel::Warning);
};

void Log::Information(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
	if (Level < LogLevel::Information) {
		return;
	}
	makemsg(dat, filename, defaultlinenumber, LogLevel::Information);
};

void Log::Debug(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
	if (Level < LogLevel::Debug) {
		return;
	}
	makemsg(dat, filename, defaultlinenumber, LogLevel::Debug);
};

void Log::Verbose(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
	if (Level < LogLevel::Verbose) {
		return;
	}
	makemsg(dat, filename, defaultlinenumber, LogLevel::Verbose);
};