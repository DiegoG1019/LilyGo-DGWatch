#ifndef DGLOGMAN_H
#define DGLOGMAN_H

#include "Arduino.h"
#include "App.h"
#include "config/config.h"
#include "config/global.h"
#include "SyncLock.h"
#include "config.h"
#include <FreeRTOS.h>
#include "ArraySequence.h"

constexpr auto defaultfilename = "Unspecified.";
constexpr auto defaultlinenumber = -1;

class Log : public App
{
public:
	enum struct LogLevel : int8_t
	{
		Fatal = 0,
		Error = 1,
		Warning = 2,
		Information = 3,
		Debug = 4,
		Verbose = 5
	};
	Log(Log::LogLevel level);
	void Initialize(void* params);
	void Run();
private:
	static bool FlushTimer(void* opaque);
	unsigned int FlushLogTimer : 1;
	unsigned int IgnoreNextTimerCall : 1;
	static void Flush();
	static bool _IsFlushing;
	static SyncLock* WriteMessageSync;
	struct Message {
		String MessageDat;
		const char* Filename;
		int16_t Linenumber;
		Log::LogLevel Level;
		const char* IssueDate;
		int FreeMem;
	};

	static void OutputSerial(Message* msg, int i);
	

	static ArraySequence<Message>* MessageBuffer;
	/// <summary>
	/// The Buffer used for the messages that are currently being flushed and/or deleted. They'll both switch places regularly.
	/// </summary>
	static ArraySequence<Message>* WorkingBuffer;
	static int FlushLimit;
	inline static void makemsg(String dat, const char* filename, int16_t linenumber, Log::LogLevel lv) {
		WriteMessageSync->Lock();
		Message* msg = MessageBuffer->Next();
		WriteMessageSync->Unlock();
		msg->Filename = filename;
		msg->Linenumber = linenumber;
		msg->MessageDat = dat;
		msg->Level = lv;
		msg->IssueDate = ttgo->rtc->formatDateTime();
	#ifdef DEBUG
		msg->FreeMem = ESP.getFreeHeap();
	#endif
	};
public:
	static LogLevel Level;

	inline static const char* LevelString(Log::LogLevel lv);
	inline static int GetBufferIndex();
	inline static int GetFlushLimit();
	inline static bool GetIsFlushing();

	inline static void Fatal(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
		makemsg(dat, filename, defaultlinenumber, LogLevel::Fatal);
	};
	inline static void Error(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
		if (Level < LogLevel::Error) {
			return;
		}
		makemsg(dat, filename, defaultlinenumber, LogLevel::Error);
	};
	inline static void Warning(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber){
		if (Level < LogLevel::Warning) {
			return;
		}
		makemsg(dat, filename, defaultlinenumber, LogLevel::Warning);
	};
	inline static void Information(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
		if (Level < LogLevel::Information) {
			return;
		}
		makemsg(dat, filename, defaultlinenumber, LogLevel::Information);
	};
	inline static void Debug(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber){
		if (Level < LogLevel::Debug) {
			return;
		}
		makemsg(dat, filename, defaultlinenumber, LogLevel::Debug);
	};
	inline static void Verbose(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber) {
		if (Level < LogLevel::Verbose) {
			return;
		}
		makemsg(dat, filename, defaultlinenumber, LogLevel::Verbose);
	};

	/// <summary>
	/// Adquires full control of thread to flush the entirety of both buffers immediately
	/// </summary>
	static void ForceFlush();
};

#endif //LOG_H