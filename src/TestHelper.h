#ifndef TESTHELPER_H
#define TESTHELPER_H

#include "VectorStore.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

class TestHelper
{
public:
    static SinglyLinkedList<float> *VOTIENEmbedding(const string &text)
    {
        SinglyLinkedList<float> *vec = new SinglyLinkedList<float>();
        stringstream ss(text);
        string word;

        while (ss >> word)
        {
            int sum = 0;
            for (char c : word)
            {
                if (c >= 'a' && c <= 'z')
                    sum += c - 'a' + 1;
                else if (c >= 'A' && c <= 'Z')
                    sum -= c - 'A' + 1;
            }
            vec->add(sum);
        }

        return vec;
    }

    static SinglyLinkedList<float> *countCharsPerWord(const string &text)
    {
        SinglyLinkedList<float> *vec = new SinglyLinkedList<float>();
        stringstream ss(text);
        string word;

        while (ss >> word)
        { // Split by spaces
            int count = 0;
            for (char c : word)
            {
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                    count++;
            }
            vec->add(count);
        }

        return vec;
    }

    static SinglyLinkedList<float> *encode(const std::string &raw)
    {
        SinglyLinkedList<float> *vec = new SinglyLinkedList<float>();
        std::stringstream ss(raw);
        float value;
        while (ss >> value)
        {
            vec->add(value);
        }
        return vec;
    }

    static SinglyLinkedList<float> *readMNISTLine(const std::string &line)
    {
        SinglyLinkedList<float> *vec = new SinglyLinkedList<float>();
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ','))
        {
            try
            {
                float num = std::stof(value);
                vec->add(num);
            }
            catch (...)
            {
                // bỏ qua nếu không phải số
            }
        }

        return vec;
    }

    static std::vector<std::string> readMNISTFile(const std::string &filename)
    {
        std::ifstream file(filename);
        std::vector<std::string> lines;
        std::string line;

        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        bool firstLine = true;
        while (std::getline(file, line))
        {
            if (firstLine)
            {
                firstLine = false; // bỏ qua dòng đầu tiên
                continue;
            }

            if (!line.empty())
                lines.push_back(line);
        }

        return lines;
    }

    template <class T>
    static T *getData(ArrayList<T> &list)
    {
        return list.data;
    }

    template <class T>
    static int getCapacity(ArrayList<T> &list)
    {
        return list.capacity;
    }

    template <class T>
    static int getCount(ArrayList<T> &list)
    {
        return list.count;
    }

    template <class T>
    static int getCursor(typename ArrayList<T>::Iterator &it)
    {
        return it.cursor;
    }

    template <class T>
    static ArrayList<T> *getList(typename ArrayList<T>::Iterator &it)
    {
        return it.pList;
    }

    template <class T>
    static int getCount(const SinglyLinkedList<T> &list)
    {
        return list.count;
    }

    // ---- Access Iterator internals ----
    template <class T>
    static typename SinglyLinkedList<T>::Node *getCurrent(const typename SinglyLinkedList<T>::Iterator &it)
    {
        return it.current;
    }
};

inline string int2str(int &i)
{
    return to_string(i);
}

inline string float2str(float &f)
{
    return to_string(f);
}

inline string double2str(double &d)
{
    return to_string(d);
}

inline string point2str(Point &p)
{
    return "(" + to_string((int)p.getX()) + "," +
           to_string((int)p.getY()) + "," +
           to_string((int)p.getZ()) + ")";
}

inline string str2str(string &s)
{
    return "\"" + s + "\"";
}

inline string char2str(char &c)
{
    return string(1, c);
}

#endif // TESTHELPER_H
