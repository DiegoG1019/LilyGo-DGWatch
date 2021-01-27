#ifndef DGLOGMAN_H
#define DGLOGMAN_H

#include "App.h"
#include "ArraySequence.h"
#include "SyncLock.h"

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
	Log(Log::LogLevel level) : App("LogManagerApp", HIGH_PRIORITY, 5, PRIMARY_CORE) {
		_StartUp = true;

		FlushLogTimer = 0;
		IgnoreNextTimerCall = 0;

		MessageBuffer = new ArraySequence<Message>(LOG_MESSAGE_BUFFER_SIZE, false, true);
		WorkingBuffer = new ArraySequence<Message>(LOG_MESSAGE_BUFFER_SIZE, false, true);
		FlushLimit = (3 * LOG_MESSAGE_BUFFER_SIZE) / 4;
		Level = level;

		WriteMessageSync = new SyncLock();
	};
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
	inline static void makemsg(String dat, const char* filename, int16_t linenumber, Log::LogLevel lv);
public:
	static LogLevel Level;

	inline static const char* LevelString(Log::LogLevel lv);
	inline static int GetBufferIndex();
	inline static int GetFlushLimit();
	inline static bool GetIsFlushing();

	inline static void Fatal(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber);
	inline static void Error(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber);
	inline static void Warning(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber);
	inline static void Information(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber);
	inline static void Debug(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber);
	inline static void Verbose(String dat, const char* filename = defaultfilename, int16_t linenumber = defaultlinenumber);

	/// <summary>
	/// Adquires full control of thread to flush the entirety of both buffers immediately
	/// </summary>
	static void ForceFlush();
};

/// <summary>
/// All functions in this class are disabled if DEBUG is not defined
/// All functions in this class are marked as inline
/// </summary>
class Debug
{
public:
	inline static uint32_t FreeRam() {
#ifdef DEBUG
		return ESP.getFreeHeap();
#endif
		return UINT32_MAX;
	};
	inline static void Assert(bool (*expr)(), char* message, const char* filename = defaultfilename, int linenumber = defaultlinenumber) {
#ifdef DEBUG
		if (expr())
			return;
		Log::Fatal(message, filename, linenumber);
		Log::ForceFlush();
		abort();
#endif
	};
	inline static void AssertError(bool (*expr)(), char* message, const char* filename = defaultfilename, int linenumber = defaultlinenumber) {
#ifdef DEBUG
		if (expr())
			return;
		Log::Error(message, filename, linenumber);
#endif
	};
	inline static void AssertWarn(bool (*expr)(), char* message, const char* filename = defaultfilename, int linenumber = defaultlinenumber) {
#ifdef DEBUG
		if (expr())
			return;
		Log::Warning(message, filename, linenumber);
#endif
	};
};

#endif //LOG_H