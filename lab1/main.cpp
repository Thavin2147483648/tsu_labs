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
bool directSortFile(const std::string &fileName, bool debug = false);
bool naturalSortFile(const std::string &fileName, bool debug = false);

int main()
{   
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    const int maxValue = 100000;
    const int numberCount = 1000000;
    const int testCount = 10;
    for (int i = 0; i < testCount; ++i)
    {
        std::cout << "Test " << i + 1 << '\n';
        createFileWithRandomNumbers("file.txt", numberCount, maxValue);
        std::cout << "Direct sort " << (directSortFile("file.txt") ? "OK" : "NOT OK") << '\n';
        std::cout << "Natural sort " << (naturalSortFile("file.txt") ? "OK" : "NOT OK") << '\n';
    }
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

bool directSortFile(const std::string& fileName, bool debug)
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
    fstream sortedFile(std::string("SORTED") + fileName, std::ios::out);
    files[0].open(fileNames[0], std::ios::in);
    while (files[0] >> number)
        sortedFile << number << ' ';
    sortedFile << '\n';
    sortedFile.close();
    files[0].close();
    return isFileContainsSortedArray(std::string("SORTED") + fileName);
}

bool naturalSortFile(const std::string& fileName, bool debug)
{
    if (isNumericFileEmpty(fileName))
        return true;
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
    int currentFile = 0, prevNumber, nextNumber;
    file >> prevNumber;
    files[currentFile] << prevNumber << ' ';
    while (file >> nextNumber)
    {
        if (nextNumber < prevNumber) {
            if (debug)
                files[currentFile] << "\n";
            currentFile = 1 - currentFile;
        }
        prevNumber = nextNumber;
        files[currentFile] << prevNumber << ' ';
    }
    file.close();
    for (int i = 0; i < 2; ++i)
        files[i].close();
    if (debug)
        system("pause");
    while (!isNumericFileEmpty(fileNames[1]))
    {
        for (int i = 0; i < 2; ++i)
            files[i] = openAndProcessFile(fileNames[i], std::ios::in);
        for (int i = 2; i < 4; ++i)
            files[i] = openAndProcessFile(fileNames[i], std::ios::out);
        int prevNumbers[2], nextNumbers[2];
        for (int i = 0; i < 2; ++i) {
            files[i] >> prevNumbers[i];
            nextNumbers[i] = prevNumbers[i];
        }
        currentFile = 0;
        while (!files[0].eof() || !files[1].eof())
        {
            while (!files[0].eof() && !files[1].eof() && !(prevNumbers[0] > nextNumbers[0]) && !(prevNumbers[1] > nextNumbers[1]))
            {
                if (nextNumbers[0] < nextNumbers[1])
                {
                    files[currentFile + 2] << nextNumbers[0] << ' ';
                    prevNumbers[0] = nextNumbers[0];
                    files[0] >> nextNumbers[0];
                }
                else
                {
                    files[currentFile + 2] << nextNumbers[1] << ' ';
                    prevNumbers[1] = nextNumbers[1];
                    files[1] >> nextNumbers[1];
                }
            }
            for (int i = 0; i < 2; ++i)
            {
                while (!files[i].eof() && !(prevNumbers[i] > nextNumbers[i]))
                {
                    files[currentFile + 2] << nextNumbers[i] << ' ';
                    prevNumbers[i] = nextNumbers[i];
                    files[i] >> nextNumbers[i];
                }
            }
            for (int i = 0; i < 2; ++i)
                prevNumbers[i] = nextNumbers[i];
            if (debug)
                files[currentFile + 2] << "\n";
            currentFile = 1 - currentFile;
        }
        std::swap(fileNames[0], fileNames[2]);
        std::swap(fileNames[1], fileNames[3]);
        for (int i = 0; i < 4; ++i)
            files[i].close();
        if (debug)
            system("pause");
    }
    fstream sortedFile(std::string("SORTED") + fileName, std::ios::out);
    files[0].open(fileNames[0], std::ios::in);
    int number;
    while (files[0] >> number)
        sortedFile << number << ' ';
    sortedFile << '\n';
    sortedFile.close();
    files[0].close();
    return isFileContainsSortedArray(std::string("SORTED") + fileName);
}
