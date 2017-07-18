#pragma once

#include <io.h>
#include <fstream>
#include <direct.h>
#include <vector>
#include <cassert>

#pragma warning(disable:4996)


namespace terra
{
	const char* kTableFileExName = "json";
	struct FileInfo_t
	{
		char file_path[256];
		char file_name[32];
		char file_ext[8];
	};
	class FileReader
	{
	public:
		FileReader(const std::string& file_path)
		{
			ReadFiles(file_path);
		}
		std::vector<FileInfo_t>& GetFileNames() { return file_infos_; }
	private:
		void ReadFiles(const std::string& file_path)
		{
			//�ļ����  
			intptr_t   hFile = 0;
			FileInfo_t fi;
			//�ļ���Ϣ  
			struct _finddata_t fileinfo;  //�����õ��ļ���Ϣ��ȡ�ṹ
			std::string temp_file_path = file_path;
			if ((hFile = _findfirst(temp_file_path.assign(file_path).append("\\*").c_str(), &fileinfo)) != -1)
			{
				do
				{
					if ((fileinfo.attrib &  _A_SUBDIR))  //�Ƚ��ļ������Ƿ����ļ���
					{
						if (strncmp(fileinfo.name, ".", 1) != 0 && strncmp(fileinfo.name, "..", 2) != 0)
						{
							//m_FileNameVec.push_back(szFilePathTmp.assign(szFilePath).append("\\").append(fileinfo.name) );
							ReadFiles(temp_file_path.assign(file_path).append("\\").append(fileinfo.name));
						}
					}
					else
					{
						ExtractFileInfo(fileinfo.name, fi.file_name, fi.file_ext);
						if (strncmp(fi.file_ext, kTableFileExName, sizeof(kTableFileExName)) == 0)
						{
							temp_file_path.assign(file_path).append("\\").append(fileinfo.name);
							strcpy(fi.file_path, temp_file_path.c_str());
							file_infos_.push_back(fi);
						}
					}
				} while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
				_findclose(hFile);
			}
		}
		bool ExtractFileInfo(char* full_name, char* file_name, char* file_ext)
		{
			//unsafe, but does not matter
			char *ext = strrchr(full_name, '.');
			if (ext)
			{
				*ext = '\0';
				strcpy(file_name, full_name);
				strcpy(file_ext, ext + 1);
				*ext = '.';
				return true;
			}
			assert(0);
			return false;
		}
	private:
		std::vector<FileInfo_t> file_infos_;
	};
}