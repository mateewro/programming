#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <functional>

using namespace std;

class PlateWithPancakes
{
public:
    
    int startEating()
    {
        auto lowerTime = INT_MAX;
        auto maxTime = *(std::max_element(m_numberOfPancakes.begin(), m_numberOfPancakes.end()));
        for (auto minValue = 1; minValue <= maxTime; ++minValue)
        {
            auto tmp = m_numberOfPancakes;
            auto time = 0;
            while(!m_numberOfPancakes.empty())
            {
                makeRound(minValue);
                ++time;
                skipWhenTimeIsTooLong(time, lowerTime);
            }
            lowerTime = min(time, lowerTime);
            m_numberOfPancakes = tmp;
        }
        return lowerTime;
    }

    void addNumberOfPancakes(int numberOfPancakes)
    {
        m_numberOfPancakes.push_back(numberOfPancakes);
    }

private:

    void removeEmptyPlates()
    {
        m_numberOfPancakes.remove(0);
    }
    
    void eatPancakes()
    {
        for (auto& plate : m_numberOfPancakes)
        {
            --plate;
        }
        removeEmptyPlates();
    }
    
    bool tryToMakeSplit(const int minValue)
    {
        auto pancakesToSplit = max_element(m_numberOfPancakes.begin(),m_numberOfPancakes.end());
        if (pancakesToSplit != end(m_numberOfPancakes))
        {
            auto tmp = *pancakesToSplit;
            auto resultOfPancakesSplit = *pancakesToSplit / 2;
            if (resultOfPancakesSplit < minValue)
            {
                return false;
            }
            *pancakesToSplit = resultOfPancakesSplit;
            m_numberOfPancakes.push_back(tmp-*pancakesToSplit);
            return true;
        }
        return false;
    }
    
    void makeRound(int minValue)
    {
        if (tryToMakeSplit(minValue))
        {
            return;
        }
        else
        {
            eatPancakes();
        }
    }
    
    void skipWhenTimeIsTooLong(int time, int lowerTime)
    {
        if (time >= lowerTime)
        {
            m_numberOfPancakes.clear();
        }
    }

    list<int> m_numberOfPancakes;
};


auto getDataFromFile(const std::string& file)
{
    vector<PlateWithPancakes> PlatesWithPancakes;
    ifstream myfile(file);
    if (myfile.is_open())
    {
        string line;
        getline(myfile,line);
        auto testcasesNumber = stoi(line);
        for (auto testCase = 0;  testCase < testcasesNumber; ++testCase)
        {
            getline(myfile,line);
            auto diners = stoi(line);
            getline(myfile,line);
            istringstream iss(line);
            PlatesWithPancakes.push_back(PlateWithPancakes());
            for (auto item = 0; item < diners; ++item)
            {
                int i;
                iss >> i;
                PlatesWithPancakes[testCase].addNumberOfPancakes(i);
            }
        }
        myfile.close();
    }
    return PlatesWithPancakes;
}


int main () {
    auto PlatesWithPancakes = getDataFromFile("input.txt");
    ofstream myfile;
    myfile.open("output.txt");
    
    if (!PlatesWithPancakes.empty())
    {
        auto numberOfTestCase = 0;
        for (auto testCase : PlatesWithPancakes)
        {
            auto a = testCase.startEating();
            myfile << "Case #" << ++numberOfTestCase << " :" << a << endl;
        }
    }
    myfile.close();
    return 0;
}
