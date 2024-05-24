#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <glob.h>
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

std::vector<std::string> getFiles(std::string directoryPath, std::string extensionName)
{
    std::vector<std::string> fileList;
    fileList.clear();
    auto lastChar = directoryPath.at(directoryPath.length() - 1);
    glob_t glob_result;
    std::string patternStr = (lastChar == '/' ? directoryPath : (directoryPath + "/")) + "*" + extensionName;
    std::cout << "patternStr:" << patternStr << std::endl;
    glob(patternStr.c_str(), 0, nullptr, &glob_result);
    for (size_t i = 0; i < glob_result.gl_pathc; i++) {
        fileList.push_back(glob_result.gl_pathv[i]);
    }
    globfree(&glob_result);
    return fileList;
}

// 检查目录内文件名并修改
bool checkFile(const std::string& directoryPath)
{
    struct stat fileInfo;
    if (fileInfo.st_mode & EISDIR)
    {
        // 目录存在
        std::vector<std::string> filenames = getFiles(directoryPath, ".stp");
        // 对文件名进行排序
        std::sort(filenames.begin(), filenames.end());
        // 遍历文件名并修改
        for (int i = 0; i < filenames.size(); ++i)
        {
            int num = i + 1;
            std::string oldFilePath = filenames[i];
            std::string newFilePath = filenames[i].substr(0, filenames[i].find_last_of('.')) + "-" \
                + (num < 10 ? ("0" + std::to_string(num)) : std::to_string(num)) + getFileExtension(filenames[i]);
            // 输出修改后的文件名
            std::cout << "Old filename: " << filenames[i] << " --> New filename: " << newFilePath << std::endl;
            // 修改文件名
            auto ret = rename(oldFilePath.c_str(), newFilePath.c_str());
            if (ret != 0)
            {
                std::cout << "Error renaming file: " << oldFilePath << std::endl;
                return false;
            }
        }
    }
    else
    {
        std::cout << "Path[" << directoryPath << "] not directory." << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory_path>" << std::endl;
        return 1;
    }
    std::string directoryPath = argv[1];
    if(!checkFile(directoryPath))
    {
        std::cerr << "检查并修改目录内*.stp文件的文件名失败.目录:" << directoryPath << std::endl;
    }
    return 0;
}
