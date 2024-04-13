/**
 * @file: ISIO.h
 * @brief io support, cross-platform support
 * @author zhangxin
 * @date 2023-3-11
 */

#ifndef _IS_IO_H
#define _IS_IO_H
#include "ISUtils.h"
#include <string>
#include <fstream>

namespace ISUtils {
	struct IOContext {
		std::string filename;
	};

	class FileFormat {
	public:
		FileFormat() = default;
		virtual ~FileFormat();
		virtual bool init(const IOContext& ctx) { return true; }
		virtual void read(char*, size_t&) = 0;
		// @ret: actually write in bytes
		virtual void write(const char*, const size_t&) = 0;
		virtual void reset();
		void close();
		size_t fileSize();
	protected:
		IOContext _ctx;
		std::fstream _fs;
	};

	// TODO: not finished
	class EXPORT_ISUTILS_ABI TextFileFormat : public FileFormat {
	public:	
		TextFileFormat() = default;
		virtual ~TextFileFormat();
		bool init(const IOContext& ctx) override;
		virtual void read(char*, size_t&) override; // readAll
		virtual void write(const char*, const size_t&) override; // writeAll
		const std::string& readLine(const std::string& context);
		const std::string& readBytes(char* buffer, const size_t&); // for string only
	private:
	};

	// TODO: bin format
	class EXPORT_ISUTILS_ABI BinFileFormat : public FileFormat {
	public:
		BinFileFormat() = default;
		virtual ~BinFileFormat();
		bool init(const IOContext& ctx) override;
		virtual void read(char*, size_t&) override;
		virtual void write(const char*, const size_t&) override; // writeAll
	private:
		static const size_t BLOCK_SIZE = 1024; // 1KB
	};
} // ISUtils

#endif // _IS_IO_H

