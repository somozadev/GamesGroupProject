#include <iostream>

int main() 
{
  int home;
  int enemy;
  std::cout<< "can I have your Earth weight Please\n";
  std::cin>> home;

   std::cout<<"Type the Number of the planet you want to fight\n";
   std::cout<<"1) Mercury ||  2) Venus || 3) Mars || 4) Jupiter \n";
    std::cout<<"5) Saturn ||  6) Uranus || 7) Neptune \n";
    std::cin>> enemy;
    
switch(enemy)
{
    case 1 :
    std::cout<<" your weight on Mercury is "<<home*enemy;
    break;
    
    default :
    std::cout<<"error\n";
    }

    }