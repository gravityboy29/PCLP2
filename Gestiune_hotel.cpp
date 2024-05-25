#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

class Hotel{
private:
    int nr_camera,nr_persoane;
    std::string tip;
    float pret;
public:
    Hotel(int nr_camera,std::string tip,int nr_persoane,float pret):
    nr_camera(nr_camera),tip(tip),nr_persoane(nr_persoane),pret(pret){}
    
    int get_nr_persoane(){
        return this->nr_persoane;
    }
    std::string get_tip(){
        return this->tip;
    }
    float get_pret(){
        return this->pret;
    }
    
    int capacitate(){
        if(tip=="single")
            return 1;
        else if(tip=="twin" || tip=="double")
            return 2;
        else
            return 3;
    }
    void afisare(){
        std::cout<<nr_camera<<" "<<tip<<" "<<nr_persoane<<" "<<pret<<"\n";
    }
    ~Hotel(){}
};

bool comp(Hotel *l, Hotel *r){
    if(l->capacitate()<r->capacitate() || (l->capacitate()==r->capacitate() && l->get_pret()<r->get_pret()))
        return true;
    else
        return false;
}

int main(){
    int test,temp_nr_camera,temp_nr_persoane;
    std::string temp_tip;
    float temp_pret;
    
    std::vector <Hotel*> vec;

    do{
        std::cin>>test;
        if(test==1){
            std::cin>>temp_nr_camera>>temp_tip>>temp_nr_persoane>>temp_pret;
            vec.push_back(new Hotel(temp_nr_camera,temp_tip,temp_nr_persoane,temp_pret));
        }
        else if(test==2){
            for(int i=0;i<vec.size();i++)
                vec[i]->afisare();
        }
        else if(test==3){
            int camere_ocupate=0;
            for(int i=0;i<vec.size();i++)
                if(vec[i]->get_nr_persoane()!=0)
                    camere_ocupate++;
            std::cout<<std::fixed<<std::setprecision(2)<<camere_ocupate*1.0/vec.size()*100<<"\n";
        }
        else if(test==4){
            int rest=0;
            for(int i=0;i<vec.size();i++){
                if(vec[i]->get_tip()=="single" && vec[i]->get_nr_persoane()==0)
                    rest=rest+1;
                else if((vec[i]->get_tip()=="twin" || vec[i]->get_tip()=="double") && vec[i]->get_nr_persoane()==0)
                    rest=rest+2;
                else if(vec[i]->get_tip()=="triple" && vec[i]->get_nr_persoane()==0)
                    rest=rest+3;
            }
            std::cout<<rest<<"\n";
        }
        else if(test==5){
            std::sort(vec.begin(),vec.end(),comp);
            for(int i=0;i<vec.size();i++)
                vec[i]->afisare();
        }
    }while(test!=-1);

    return 0;
}
