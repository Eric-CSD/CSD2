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
	// setter and getter for the distance between read and write head
	void setDistanceRW(uint distanceRW);
  uint getDistanceRW();
	// write and read values at write / read head
	inline void write(float val) { m_buffer[m_writeH] = val; }
	inline float read() { return m_buffer[m_readH]; }

  // increase write and read heads with 1 or more samples and wrap if necessary
	inline void incrWriteH() {
		m_writeH++;
		wrapH(m_writeH);
	}
	inline void incrReadH() {
		m_readH++;
		wrapH(m_readH);
	}

	inline void incrReadH(uint ticks) {
		m_readH += ticks;
		wrapH(m_readH);
	}

  // wrap a head if necessary
	inline void wrapH(uint& head) {
		if (head >= m_size) head -= m_size;
	}



	// debug methods
	void logRWPos();
  void logDistanceRW();
  void logSize();
  void logAllSettings();
	void logAllValues();

private:
  void allocateBuffer();
  void releaseBuffer();

	float* m_buffer;
	uint m_size;
	// read and write heads
	uint m_readH;
	uint m_writeH;
	uint m_distanceRW;
};
