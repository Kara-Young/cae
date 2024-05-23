#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h> 
#include <sys/stat.h> 
#include <cstring>

// 获取文件名的扩展名
std::string getFileExtension(const std::string& filename)
{
    size_t dotIndex = filename.find_last_of(".");
    if (dotIndex != std::string::npos) {
        return filename.substr(dotIndex);
    }
    return "";
}

// 修改文件名
void renameFiles(const std::string& directoryPath)
{
    DIR* dir = opendir(directoryPath.c_str());
    if (dir == nullptr) {
        std::cerr << "Error opening directory" << std::endl;
        return;
    }

    struct dirent* entry;
    std::vector<std::string> filenames;

    // 遍历目录获取文件名
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_REG)
        { // 只处理普通文件
            std::string filename = entry->d_name;
            std::string extension = getFileExtension(filename);
            if (extension == ".stp" || extension == ".STP")
            { 
                // 找到目标扩展名文件
                filenames.push_back(filename);
            }
        }
    }
    closedir(dir);

    // 对文件名进行排序
    std::sort(filenames.begin(), filenames.end());

    // 遍历文件名并修改
    for (int i = 0; i < filenames.size(); ++i)
    {
        int num = i + 1;
        std::string oldFilePath = directoryPath + "/" + filenames[i];
        std::string newFilename = filenames[i].substr(0, filenames[i].find_last_of('.')) + "-" \
            + (num < 10 ? ("0" + std::to_string(num)) : std::to_string(num)) + getFileExtension(filenames[i]);
        std::string newFilePath = directoryPath + "/" + newFilename;
        // 输出修改后的文件名
        std::cout << "Old filename: " << filenames[i] << " --> New filename: " << newFilename << std::endl;
        // 修改文件名
        if (rename(oldFilePath.c_str(), newFilePath.c_str()) != 0)
        {
            std::cerr << "Error renaming file: " << filenames[i] << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory_path>" << std::endl;
        return 1;
    }
    std::string directoryPath = argv[1];
    renameFiles(directoryPath);
    return 0;
}
