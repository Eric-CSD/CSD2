
#pragma once

typedef unsigned int uint;

class CircBuffer {
public:
	/*
	 * size: the number of samples in the buffer
	 */

	CircBuffer();
	CircBuffer(uint size);
	~CircBuffer();

	void resetSize(uint size);
	void allocateBuffer();
	void releaseBuffer();

	// set the distance between read and write head)
	void setDistanceRW(uint distanceRW);

	// write and read values at write / read head
	inline void write(float val) { m_buffer[m_writeH] = val; }
	inline float read() { return m_buffer[m_readH]; }
	// inline float readWithOffset(uint offset) {
	// 	// add read head to offset and
	// 	offset += m_readH;
	// 	wrapH(offset);
	// 	return m_buffer[offset];
	// }
	inline uint getDistanceRW() { return m_distanceRW; }
	inline void incrWriteH() {
		m_writeH++;
		wrapH(m_writeH);
	}
	inline int incrReadH() {
		m_readH++;
		wrapH(m_readH);
		return m_readH;
	}

	inline void incrReadH(uint ticks) {
		m_readH += ticks;
		wrapH(m_readH);
	}

	inline void wrapH(uint& head) {
		if (head >= m_size) head -= m_size;
	}

	// debug methods
	void logRWPos();
  void logDistanceRW();
  void logSize();
  void logAllSettings();
	void logAllValues();

	float* m_buffer;
	uint m_size;
	// read and write heads
	uint m_readH;
	uint m_writeH;
	uint m_distanceRW;
};
