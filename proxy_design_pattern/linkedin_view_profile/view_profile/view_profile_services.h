#pragma once
#include<vector>
#include<iostream>
#include "view_profile.h"
#include "../user.h"
#include "unordered_map"
using namespace std;

class ProfileViewService: public IProfileView{
    private:
    unordered_map<int, vector<User>>viewers;
    public:
    void addProfileViewer(int profileId, User& viewer){
        viewers[profileId].push_back(viewer);
    }

    vector<User> getProfileViewer(int profileId, User& currUser)override{
        return viewers[profileId];
    }

    virtual ~ProfileViewService()=default;

};