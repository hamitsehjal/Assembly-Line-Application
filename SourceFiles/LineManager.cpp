

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"

namespace sdds {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        std::ifstream fileObj(file);
        if (!fileObj)
            throw "Failed to open the file";
        else {
            Utilities utility;
            bool more{true};
            size_t npos = 0;

            std::string readLine, currentStationName, nextStationName;

            Workstation* firstWorkStation{ nullptr };
            Workstation* currentWorkStation{ nullptr };
            Workstation* nextWorkStation{ nullptr };

            while (std::getline(fileObj, readLine))
            {
               
                npos = 0;
                currentStationName = utility.extractToken(readLine, npos, more);
                currentWorkStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getItemName() == currentStationName;
                    });
                activeLine.push_back(currentWorkStation);

                if (more) {
                    nextStationName = utility.extractToken(readLine, npos, more);
                    nextWorkStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                        return station->getItemName() == nextStationName;
                        });
                    currentWorkStation->setNextStation(nextWorkStation);
                }
            }

           for_each(stations.begin(), stations.end(), [&](Workstation* temp) {
                firstWorkStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getNextStation() == firstWorkStation;
                    });
               });

            m_firstStation = firstWorkStation;
        }
        fileObj.close();
        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {
        const Workstation* station = m_firstStation;
        size_t i{ 0 };
        do
        {
            activeLine[i++] = const_cast<Workstation*>(station);
            station = station->getNextStation();
        } while (station != nullptr);
    }

    bool LineManager::run(std::ostream& os) {
        static size_t noOfIterations{ 0 };
        os << "Line Manager Iteration: " << ++noOfIterations << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* station) {
            station->fill(os);
            });
        std::for_each(activeLine.begin(), activeLine.end(), [](Workstation* station) {
            station->attemptToMoveOrder();
            });

        return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
    }

    void LineManager::display(std::ostream& os) const
    {
        if (!activeLine.empty())
        {
            std::for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* station){
                station->display(os);
                });
        }
    
    }
}
