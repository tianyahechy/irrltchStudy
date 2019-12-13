#pragma once
#include "IUnknown.h"
#include "IReadFile.h"
#include "array.h"
#include "irrstring.h"

namespace irr
{
	namespace io
	{
		const s16 ZIP_FILE_ENCRYPTED = 0x0001;
		const s16 ZIP_INFO_IN_DATA_DESCRIPTOR = 0x0008;
#ifdef _MSC_VER
#pragma pack(push, packing)
#pragma pack(1)
#define PACK_STRUCT
#elif defined(__GNUC__)
#define PACK_STRUCT __attribute__ ((packed))
#else
	error compiler not supported
#endif // _MSC_VER

		struct SZIPFileDataDescriptor
		{
			s32 CRC32;
			s32 CompressedSize;
			s32 UncompressedSize;
		}PACK_STRUCT;

		struct SZIPFileHeader
		{
			s32 Sig;
			s16 VersionToExtract;
			s16 GeneralBitFlag;
			s16 CompressionMethod;
			s16 LastModFileTime;
			s16 LastModFileDate;
			SZIPFileDataDescriptor DataDescriptor;
			s16 FileNameLength;
			s16 ExtraFieldLength;
		}PACK_STRUCT;
#ifdef _MSC_VER
#pragma pack(pop, packing)
#endif // _MSC_VER
		template <class T>
		struct SZipFileEntry
		{
			core::string zipFileName;
			core::string simpleFileName;
			core::string path;
			s32 fileDataPosition;
			SZIPFileHeader header;

			bool operator< (const SZipFileEntry& other) const
			{
				return simpleFileName < other.simpleFileName;
			}

			bool operator== (const SZipFileEntry& other) const
			{
				return simpleFileName == other.simpleFileName;
			}
		};
		
		//template<class T>
		class CZipReader : public IUnkown
		{
		private:
			IReadFile * _file;
			core::array<SZipFileEntry> _fileList;
			bool _ignoreCase;
			bool _ignorePaths;

			bool scanLocalHeader();
			void extractFileName(SZipFileEntry* entry);
			void deletePathFromFileName(core::string& fileName);

		public:
			CZipReader(IReadFile* file, bool ignoreCase, bool ignorePaths);
			virtual ~CZipReader();
			virtual IReadFile* openFile(const c8* fileName);
			IReadFile * openFile(s32 index);
			s32 getFileCount();
			const SZipFileEntry* getFileInfo(s32 index) const;
			s32 findFile(const c8* fileName);
		};
	}
}