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

#include "Core.h"

List<FileManager::File*> FileManager::mFiles;

#ifdef PLATFORM_WINDOWS
void FileManager::File::open(const char& filename)
{
	mFile = CreateFile(&filename,GENERIC_READ, FILE_SHARE_READ, NULL,OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);
	if(mFile != INVALID_HANDLE_VALUE)
	{
		mStatus = FILESTATUS_READING;
	}
	else
	{
		mStatus = FILESTATUS_FAILED;
	}
}

U32 FileManager::File::run()
{
	if(mStatus == FILESTATUS_READING)
	{
		mLength = GetFileSize(mFile,NULL);
		mData = new U8[mLength];
		if(mData)
		{
			DWORD read = 0;
			ReadFile(mFile, mData,mLength,&read,NULL);

			if(read == mLength)
			{
				mStatus = FILESTATUS_SUCCESS;
			}
			else
			{
				mStatus = FILESTATUS_FAILED;
			}
		}
		CloseHandle(mFile);
	}

	mFile = NULL;

	return 0;
}
#endif


#ifdef PLATFORM_WASM
void FileManager::File::downloadSucceeded(emscripten_fetch_t *fetch)
{
	printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);

	FileManager::File* file = (FileManager::File*)fetch->userData;
	if(file)
	{
		file->mLength = fetch->numBytes;
		file->mData = new U8[file->mLength];
		if(file->mData)
		{
			memcpy(file->mData, fetch->data, file->mLength);
		}
	}

	emscripten_fetch_close(fetch);
}

void FileManager::File::downloadFailed(emscripten_fetch_t *fetch)
{
	printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
	FileManager::File* file = (FileManager::File*)fetch->userData;
	if (file)
	{
		file->mStatus = FILESTATUS_FAILED;
	}
	emscripten_fetch_close(fetch);
}
#endif

const FileManager::File* FileManager::openFile(const char& filename)
{
	FileManager::File* ret = new FileManager::File();
#ifdef PLATFORM_WINDOWS
	ret->open(filename);
	ret->start();
#elif defined(PLATFORM_WASM)
	ret->mStatus = File::FILESTATUS_READING;

	emscripten_fetch_attr_t attr;
	emscripten_fetch_attr_init(&attr);
	strcpy(attr.requestMethod, "GET");
	attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
	attr.onsuccess = FileManager::File::downloadSucceeded;
	attr.onerror = FileManager::File::downloadFailed;
	attr.userData = ret;
	emscripten_fetch(&attr, &filename);

#endif

	mFiles.add(ret);

	return ret;
}