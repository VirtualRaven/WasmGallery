#include "layout.hpp"
#include "allData.hpp"
#include <iostream>
#include <string>
int main()
{
    Layout::calcScaleFactors({1500,100,4.0,10.0});
    auto row = Calculated::Row[0];
    for( int i = 0; i< Data::NumPictures; i++ ){
        std::string s(" ");
        if(i==0){
            s="";
        }
        if(row!=Calculated::Row[i]){
            s="\n";
        }
        std::cout<< s <<"#";
        row=Calculated::Row[i];
    }
    std::cout<<std::endl;

}