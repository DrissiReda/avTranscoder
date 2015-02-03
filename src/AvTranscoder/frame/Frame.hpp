#ifndef _AV_TRANSCODER_FRAME_FRAME_HPP_
#define _AV_TRANSCODER_FRAME_FRAME_HPP_

#include <AvTranscoder/common.hpp>

extern "C" {
#include <libavcodec/avcodec.h>
}

namespace avtranscoder
{

class AvExport Frame
{
public:
	/// Create a frame with empty buffer data
	Frame();

	/// Create a frame with a the given buffer size
	Frame( const size_t dataSize, const int value );

	/// Create a frame from the given AVPAcket (copy data)
	Frame( AVPacket& avPacket );

	/// Free buffer of data
	~Frame();

	/// Resize data buffer
	void resize( const size_t newSize );

	///@{
	/// Ref to external data buffer
	void refData( Frame& frame );
	void refData( unsigned char* buffer, const size_t size );
	///@}

	/**
	 * @brief Resize the buffer with the given size, and copy the given value
	 * @note Use this function to check if we can modify the buffer
	 */
	void assign( const size_t size, const int value );

	/// Clear existing data and set size to 0
	void clear();

	AVPacket& getAVPacket() { return _packet; }
	unsigned char* getData() { return _packet.data; }
	size_t getSize() const { return _packet.size; }

#ifndef SWIG
	const AVPacket& getAVPacket() const { return _packet; }
	const unsigned char* getData() const { return _packet.data; }
#endif

private:
	void initAVPacket();

private:
	AVPacket _packet;
};

// Typedef to represent buffer of coded data.
// Example 1: in case of image, no sense to get size if coded data.
// Example 2: in case of audio, no sense to get number of channels if coded data.
typedef Frame CodedData;

}

#endif
