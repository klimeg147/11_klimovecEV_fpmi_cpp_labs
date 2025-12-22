#pragma once

#include <string>
#include <iostream>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};


class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train()
        : id_(0),
          type_(TrainType::PASSENGER),
          destination_(""),
          dispatch_time_(0),
          travelling_time_(0) {
    }

    Train(TrainId id, TrainType type, const std::string& dest, std::time_t dispatch,
          std::time_t travelling)
        : id_(id),
          type_(type),
          destination_(dest),
          dispatch_time_(dispatch),
          travelling_time_(travelling) {
    }

    TrainId GetId() const {
        return id_;
    }

    TrainType GetType() const {
        return type_;
    }

    std::string GetDestination() const {
        return destination_;
    }

    std::time_t GetDispatchTime() const {
        return dispatch_time_;
    }

    std::time_t GetTravellingTime() const {
        return travelling_time_;
    }

    void SetId(TrainId id) {
        id_ = id;
    }

    void SetType(TrainType type) {
        type_ = type;
    }

    void SetDestination(const std::string& dest) {
        destination_ = dest;
    }

    void SetDispatchTime(std::time_t time) {
        dispatch_time_ = time;
    }

    void SetTravellingTime(std::time_t time) {
        travelling_time_ = time;
    }

    void Print() const {
        std::cout << "Train " << id_ << ": ";
        switch (type_) {
            case TrainType::PASSENGER:
                std::cout << "Passenger";
                break;
            case TrainType::FREIGHT:
                std::cout << "Cargo";
                break;
            case TrainType::HIGH_SPEED:
                std::cout << "Express";
                break;
            case TrainType::SUBWAY:
                std::cout << "Subway";
                break;
            case TrainType::SPECIALIZED:
                std::cout << "Specialized";
                break;
        }

        std::cout << "/ destination: " << destination_;
        std::cout << "/ dispatch time: ";
        time_utility::PrintTime(dispatch_time_);
        std::cout << "/ travelling time: ";
        time_utility::PrintTime(travelling_time_);
    }
};