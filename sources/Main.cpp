#include <iostream>
#include <string>
#include "OrgChart.hpp"

using namespace ariel;
int main(){
    //create OrgChart
    OrgChart org;
    while (true)
    {
        std::string ans;
        std::cout << "hello! what you want to do? to exit enter 'x'." << std::endl;
        //enter action
        std::cin >> ans;
        //if ans == x exit
        if(ans == "x"){
            std::cout << "bye bye" << std::endl;
            break;
        } 
        //add root
        else if(ans == "root"){
            std::string name;
            std::cout << "please enter the root name" << std::endl;
            std::cin >> name;
            org.add_root(name);
        }
        //try add sub
        else if(ans == "sub"){
            std::string boss;
            std::string name;
            std::cout << "please enter the boss name" << std::endl;
            std::cin >> boss;
            std::cout << "please enter the employee name" << std::endl;
            std::cin >> name;
            try{
                org.add_sub(boss, name);
            }
            //print the exeption
            catch (std::exception& e){
                std::cout << e.what() << std::endl;
            }
        }
        //print the chart
        else if(ans == "print"){
            std::cout << org << std::endl;
        }
    }
    return 0;
}