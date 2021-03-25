#ifndef DG_SYNC_LOCK_h
#define DG_SYNC_LOCK_h

class SyncLock
{
private:
	SemaphoreHandle_t handle;
public:
	SyncLock() {
		handle = xSemaphoreCreateBinary();
		Unlock();
	};
	SyncLock(SyncLock&) = delete;
	void Unlock() {
		xSemaphoreGive(handle);
	};
	bool Lock(uint32_t delay = portMAX_DELAY) {
		if (delay != portMAX_DELAY) {
			delay = pdMS_TO_TICKS(delay);
		}
		return xSemaphoreTake(handle, delay);
	};
};

#endif