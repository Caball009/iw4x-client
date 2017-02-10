#include "STDInclude.hpp"

namespace Utils
{
	namespace IO
	{
		bool FileExists(std::string file)
		{
			return std::ifstream(file).good();
		}

		bool WriteFile(std::string file, std::string data, bool append)
		{
			auto pos = file.find_last_of("/\\");
			if (pos != std::string::npos)
			{
				CreateDirectory(file.substr(0, pos));
			}

			std::ofstream stream(file, std::ios::binary | std::ofstream::out | (append ? std::ofstream::app : std::ofstream::out));

			if (stream.is_open())
			{
				stream.write(data.data(), data.size());
				stream.close();
				return true;
			}

			return false;
		}

		std::string ReadFile(std::string file)
		{
			std::string data;
			ReadFile(file, &data);
			return data;
		}

		bool ReadFile(std::string file, std::string* data)
		{
			if (!data) return false;
			data->clear();

			if (FileExists(file))
			{
				std::ifstream stream(file, std::ios::binary);
				if (!stream.is_open()) return false;

				stream.seekg(0, std::ios::end);
				std::streamsize size = stream.tellg();
				stream.seekg(0, std::ios::beg);

				if (size > -1)
				{
					data->resize(static_cast<uint32_t>(size));
					stream.read(const_cast<char*>(data->data()), size);
					stream.close();
					return true;
				}

				stream.close();
			}

			return false;
		}

		bool CreateDirectory(std::string dir)
		{
			return std::experimental::filesystem::create_directories(dir);
		}

		std::vector<std::string> ListFiles(std::string dir)
		{
			std::vector<std::string> files;

			for (auto& file : std::experimental::filesystem::directory_iterator(dir))
			{
				files.push_back(file.path().generic_string());
			}

			return files;
		}
	}
}
