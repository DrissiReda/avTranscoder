#include "Frame.hpp"

namespace avtranscoder
{

Frame::Frame()
{
	initAVPacket();
}

Frame::Frame( const size_t dataSize, const int value )
{
	av_new_packet( &_packet, dataSize );
	assign( dataSize, value );
}

Frame::Frame(AVPacket& avPacket)
{
	av_copy_packet( &_packet, &avPacket );
}

Frame::~Frame()
{
	av_free_packet( &_packet );
}

void Frame::resize( const size_t newSize )
{
	if( (int) newSize < _packet.size )
		av_shrink_packet( &_packet, newSize );
	 else if( (int) newSize > _packet.size )
		av_grow_packet( &_packet, newSize );
	memset( _packet.data, 0, _packet.size );
}

void Frame::refData( unsigned char* buffer, const size_t size )
{
	_packet.data = buffer;
	_packet.size = size;
}

void Frame::refData( Frame& frame )
{
	_packet.data = frame.getData();
	_packet.size = frame.getSize();
}

void Frame::clear()
{
	av_free_packet( &_packet );
	initAVPacket();
}

void Frame::assign( const size_t size, const int value )
{
	resize( size );
	memset( _packet.data, value, size );
}

void Frame::initAVPacket()
{
	av_init_packet( &_packet );
	_packet.data = NULL;
	_packet.size = 0;
}

}
