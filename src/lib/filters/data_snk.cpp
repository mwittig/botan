/*
* DataSink
* (C) 1999-2007 Jack Lloyd
*     2005 Matthew Gregan
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#include <botan/data_snk.h>
#include <botan/exceptn.h>

#if defined(BOTAN_TARGET_OS_HAS_FILESYSTEM)
  #include <fstream>
#endif

namespace Botan {

/*
* Write to a stream
*/
void DataSink_Stream::write(const uint8_t out[], size_t length)
   {
   m_sink.write(reinterpret_cast<const char*>(out), length);
   if(!m_sink.good())
      throw Stream_IO_Error("DataSink_Stream: Failure writing to " +
                            m_identifier);
   }

/*
* DataSink_Stream Constructor
*/
DataSink_Stream::DataSink_Stream(std::ostream& out,
                                 const std::string& name) :
   m_identifier(name),
   m_sink(out)
   {
   }

#if defined(BOTAN_TARGET_OS_HAS_FILESYSTEM)

/*
* DataSink_Stream Constructor
*/
DataSink_Stream::DataSink_Stream(const std::string& path,
                                 bool use_binary) :
   m_identifier(path),
   m_sink_memory(new std::ofstream(path, use_binary ? std::ios::binary : std::ios::out)),
   m_sink(*m_sink_memory)
   {
   if(!m_sink.good())
      {
      throw Stream_IO_Error("DataSink_Stream: Failure opening " + path);
      }
   }
#endif

/*
* DataSink_Stream Destructor
*/
DataSink_Stream::~DataSink_Stream()
   {
   // for ~unique_ptr
   }

}
