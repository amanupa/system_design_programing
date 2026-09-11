#pragma once 
#include "../user.h"
#include "view_profile.h"
#include "view_profile_services.h"
#include "../subscription_type.h"
#include<iostream>
#include<vector>
using namespace std;

class ProfileViewProxy : public IProfileView{
    private:
    ProfileViewService& services;

    public:
    ProfileViewProxy(ProfileViewService& service):services(service){}

    vector<User>getProfileViewer(int id, User& curruser)override{
        auto viewers=services.getProfileViewer(id,curruser);
        if(curruser.getSubscriptionType()==SubscriptionType::PREMIUM){
            return viewers;

        }
        vector<User> result;

        int n = viewers.size();

        for(int i=max(0,n-2);i<n;i++)
            result.push_back(viewers[i]);

        return result;

    }
};