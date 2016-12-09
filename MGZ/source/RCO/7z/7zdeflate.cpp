#include "7z.h"

#include "DeflateEncoder.h"

extern "C" int compress_deflate_7z(const unsigned char* in_data, unsigned in_size,
				    unsigned char* out_data, unsigned *out_size, unsigned num_passes, unsigned num_fast_bytes)
{
		NDeflate::NEncoder::CCoder cc;

		if (cc.SetEncoderNumPasses(num_passes) != S_OK)
			return false;

		if (cc.SetEncoderNumFastBytes(num_fast_bytes) != S_OK)
			return false;

		ISequentialInStream in(reinterpret_cast<const char*>(in_data), in_size);
		ISequentialOutStream out(reinterpret_cast<char*>(out_data), *out_size);

		UINT64 in_size_l = in_size;

		if (cc.Code(&in, &out, &in_size_l) != S_OK)
			return false;

		*out_size = out.size_get();

		if (out.overflow_get())
			return false;

		return true;
}
