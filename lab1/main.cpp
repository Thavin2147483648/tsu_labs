#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <string>
#include <cstdlib>

using std::fstream;

std::mt19937 generator;

fstream openAndProcessFile(const std::string &fileName, std::ios_base::openmode mode);
bool createFileWithRandomNumbers(const std::string &fileName, const int numbersCount, const int maxNumberValue);
bool isFileContainsSortedArray(const std::string &fileName);
bool isNumericFileEmpty(const std::string &fileName);
void directSortFile(const std::string &fileName, bool debug = false);

int main()
{   
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    createFileWithRandomNumbers("file.txt", 10000, 1000000);
    directSortFile("file.txt");
    return 0;
}

fstream openAndProcessFile(const std::string &fileName, std::ios_base::openmode mode)
{
    fstream stream(fileName, mode);
    if (!stream)
    {
        std::cout << "File opening error!\n";
        exit(-1);
    }
    return stream;
}

bool createFileWithRandomNumbers(const std::string &fileName, const int numbersCount, const int maxNumberValue)
{
    fstream out(fileName, std::ios::out);
    if (!out)
        return false;
    for (int i = 0; i < numbersCount; ++i)
        out << generator() % (maxNumberValue + 1) << ' ';
    out << '\n';
    out.close();
    return true;
}

bool isFileContainsSortedArray(const std::string &fileName)
{
    fstream in = openAndProcessFile(fileName, std::ios::in);
    int prev, next;
    in >> prev;
    bool flag = true;
    while ((in >> next) && flag)
    {
        if (next < prev)
            flag = false;
        prev = next;
    }
    in.close();
    return flag;
}

bool isNumericFileEmpty(const std::string& fileName)
{
    fstream file = openAndProcessFile(fileName, std::ios::in);
    int number;
    bool res = true;
    if (file >> number)
        res = false;
    file.close();
    return res;
}

void directSortFile(const std::string& fileName, bool debug)
{
    fstream file = openAndProcessFile(fileName, std::ios::in);
    std::string fileNames[4];
    fstream files[4];
    {
        std::string currentFileName = std::string("A") + fileName;
        for (int i = 0; i < 4; ++i)
        {
            currentFileName[0] = 'A' + i;
            fileNames[i] = currentFileName;
        }
    }
    for (int i = 0; i < 2; ++i)
        files[i] = openAndProcessFile(fileNames[i], std::ios::out);
    int currentFile = 0, number;
    while (file >> number)
    {
        files[currentFile] << number << ' ';
        if (debug)
            files[currentFile] << "\n";
        currentFile = 1 - currentFile;
    }
    file.close();
    for (int i = 0; i < 2; ++i)
        files[i].close();
    if (debug)
        system("pause");
    int p = 1;
    while (!isNumericFileEmpty(fileNames[1]))
    {
        for (int i = 0; i < 2; ++i)
            files[i] = openAndProcessFile(fileNames[i], std::ios::in);
        for (int i = 2; i < 4; ++i)
            files[i] = openAndProcessFile(fileNames[i], std::ios::out);
        int numbers[2], indexes[2];
        for (int i = 0; i < 2; ++i)
            files[i] >> numbers[i];
        currentFile = 0;
        while (!files[0].eof() || !files[1].eof())
        {
            for (int i = 0; i < 2; ++i)
                indexes[i] = 0;
            while (!files[0].eof() && !files[1].eof() && indexes[0] < p && indexes[1] < p)
            {
                if (numbers[0] < numbers[1])
                {
                    files[currentFile + 2] << numbers[0] << ' ';
                    ++indexes[0];
                    files[0] >> numbers[0];
                }
                else
                {
                    files[currentFile + 2] << numbers[1] << ' ';
                    ++indexes[1];
                    files[1] >> numbers[1];
                }
            }
            for (int i = 0; i < 2; ++i)
            {
                while (!files[i].eof() && indexes[i] < p)
                {
                    files[currentFile + 2] << numbers[i] << ' ';
                    ++indexes[i];
                    files[i] >> numbers[i];
                }
            }
            if (debug)
                files[currentFile + 2] << "\n";
            currentFile = 1 - currentFile;
        }
        p *= 2;
        std::swap(fileNames[0], fileNames[2]);
        std::swap(fileNames[1], fileNames[3]);
        for (int i = 0; i < 4; ++i)
            files[i].close();
        if (debug)
            system("pause");
    }
    if (!isFileContainsSortedArray(fileNames[0])) {
        std::cout << "File is not sorted!\n";
        exit(-1);
    }
    fstream sortedFile(std::string("SORTED") + fileName, std::ios::out);
    files[0].open(fileNames[0], std::ios::in);
    while (files[0] >> number)
        sortedFile << number << ' ';
    sortedFile << '\n';
    sortedFile.close();
    files[0].close();
}
