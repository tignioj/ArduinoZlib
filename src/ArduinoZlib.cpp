#include "ArduinoZlib.h"



ArduinoZlib::ArduinoZlib(){
	
}
static void error(String msg) {
  Serial.print("!!!ERROR:");
  Serial.println(msg);
}

//https://www.programcreek.com/cpp/?code=Looking4Group%2FL4G_Core%2FL4G_Core-master%2Ftools%2Flibmpq%2Flibmpq%2Fextract.c
int32_t ArduinoZlib::libmpq__decompress_zlib(uint8_t *in_buf, uint32_t in_size, uint8_t *out_buf, uint32_t out_size, uint32_t &outprintsize) {

	/* some common variables. */
	int32_t result = 0;
	int32_t tb     = 0;
  	outprintsize=0;
	z_stream z;

	/* fill the stream structure for zlib. */
	z.next_in   = (Bytef *)in_buf;
	z.avail_in  = (uInt)in_size;
	z.total_in  = in_size;
	z.next_out  = (Bytef *)out_buf;
	z.avail_out = (uInt)out_size;
	z.total_out = 0;
	z.zalloc    = NULL;
	z.zfree     = NULL;
  
  if((result=inflateInit2(&z, MAX_WBITS|32)) != Z_OK) {
  
  // if((result=inflateInit2(&z, 47)) != Z_OK) {
    error("something on zlib initialization failed.");
      return result;
  }

	/* call zlib to decompress the data. */
	if ((result = inflate(&z, Z_FINISH)) != Z_STREAM_END) {
    error("inflate something on zlib decompression failed");
    Serial.println(result);
		/* something on zlib decompression failed. */
		return result;
	}

	/* save transferred bytes. */
	tb = z.total_out;

	/* cleanup zlib. */
	if ((result = inflateEnd(&z)) != Z_OK) {
    error("something on zlib finalization failed.");
		/* something on zlib finalization failed. */
		return result;
	}

	/* return transferred bytes. */
  Serial.println("decompress success!");
    outprintsize=tb;
    Serial.println(tb);
	return tb;
} 
