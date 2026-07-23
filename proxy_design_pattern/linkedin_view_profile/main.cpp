#include<iostream>
#include "user.h"
#include "subscription_type.h"
#include "view_profile/view_profile.h"
#include "view_profile/view_profile_proxy.h"
#include "view_profile/view_profile_services.h"
using namespace std;

int main() {

    User aman(
        1,
        "Aman",
        "Something",
        SubscriptionType::FREE
    );

    User john(
        2,
        "John",
        "Software Engineer",
        SubscriptionType::PREMIUM
    );

    User alice(
        3,
        "Alice",
        "Hr Manager",
        SubscriptionType::FREE
    );

    User bob(
        4,
        "Bob",
        "Product Engineer",
        SubscriptionType::FREE
    );

    ProfileViewService realService;

    realService.addProfileViewer(1, john);
    realService.addProfileViewer(1, alice);
    realService.addProfileViewer(1, bob);
    realService.addProfileViewer(2, aman);
    realService.addProfileViewer(2, alice);
    realService.addProfileViewer(2, bob);

    ProfileViewProxy proxy(realService);

    auto freeResult =
        proxy.getProfileViewer(
            1,
            aman
        );
        cout<<"================free acount===================="<<endl;
        cout<<" "<<endl;
        for(int i=0;i<freeResult.size();i++){
            cout<<freeResult[i].getUserName()<<" viewed your profile"<<endl;
        }
        cout<<" "<<endl;
        cout<<"Active your premium subscription to see all viewers"<<endl;

    auto premiumResult =
        proxy.getProfileViewer(
            2,
            john
        );
        cout<<" "<<endl;
        cout<<"================Premium acount===================="<<endl;
        cout<<" "<<endl;
        for(int i=0;i<premiumResult.size();i++){
            cout<<premiumResult[i].getUserName()<<" viewed your profile"<<endl;
        }
}