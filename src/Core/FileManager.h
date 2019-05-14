/**
 * Code developed and maintained by Sharded-Games.
 * Licensed under the GPLv3
 *
 * @author Dave Cotterill
 *
 * (c)2018 ShardedGames.com, https://github.com/sharded-gaming/opengl-cross-platform-example
 *
 * Please keep this notice here AS IS going forward.
 * ShardedGames and the author provide no warranty and liability for the code provided AS IS.
 */

#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

/**
 * Creates a 'Threaded' or Synchronus way to download a file or open a file depending on platform
 */
class FileManager {
public:
#ifdef PLATFORM_WINDOWS
	class File : public Thread {
#else
	class File {
#endif
		private:
			friend class FileManager;
			typedef enum __tagStatus{
				FILESTATUS_INITIALISE = 0,
				FILESTATUS_READING,
				FILESTATUS_FAILED,
				FILESTATUS_SUCCESS
			} fileStatus;

#ifdef PLATFORM_WINDOWS
			HANDLE mFile;
#endif
			fileStatus mStatus;

			U8* mData;
			U32 mLength;

		public:
			File() : mStatus(FILESTATUS_INITIALISE), mData(NULL), mLength(0) {}
			~File() { SAFEDELETE(mData); mLength = 0; }

			bool isComplete() const { return mStatus == FILESTATUS_SUCCESS; }
			bool isFailed() const { return mStatus == FILESTATUS_FAILED; }

			inline U32			getLength() { return mLength; }
			inline const U8*	getDataPointer() { return mData; }

#ifdef PLATFORM_WINDOWS
			void open(const char& filename);
			U32 run();
#elif defined(PLATFORM_WASM)
			static void downloadSucceeded(emscripten_fetch_t *fetch);
			static void downloadFailed(emscripten_fetch_t *fetch);
#endif
	};

private:
	static List<File*> mFiles;

protected:
	FileManager() {}

public:
	static const File* openFile(const char& filename);
	static const File* openFile(const char* filename) { return openFile(*filename); }

};


#endif //__FILEMANAGER_H__