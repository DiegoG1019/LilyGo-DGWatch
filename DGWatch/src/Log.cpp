#include "Log.h"
#include <new>

Log::Log(): App("LogManagerApp", HIGH_PRIORITY, 5, PRIMARY_CORE){
	ttgo = TTGOClass::getWatch();
	_StartUp = true;

	FlushLogTimer = 0;
	IgnoreNextTimerCall = 0;

	MessageBuffer = ps_new (ArraySequence<Message>, LOG_MESSAGE_BUFFER_SIZE, false, true);
	WorkingBuffer = ps_new (ArraySequence<Message>, LOG_MESSAGE_BUFFER_SIZE, false, true);
	FlushLimit = (3 * LOG_MESSAGE_BUFFER_SIZE) / 4;
	WriteMessageSync = new SyncLock();
};

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
	Serial.printf(LOGFORMAT( 
			i, 
			msg->IssueDate,
			Log::LevelString(msg->Level),
			msg->Filename,
			msg->Linenumber,
			msg->MessageDat,
			MemoryUnits(msg->FreeMem, 2)));
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
		if (Serial)
			OutputSerial(msg, i);
	}
	WorkingBuffer->Index = 0;

	if (Serial)
		Serial.println("Message Buffer flush");
	for (int i = 0; i < MessageBuffer->Index; i++) {
		msg = MessageBuffer->GetPointer(i);
		//Output the logs somewhere...
		if (Serial)
			OutputSerial(msg, i);
	}
	MessageBuffer->Index = 0;
	WriteMessageSync->Unlock();
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