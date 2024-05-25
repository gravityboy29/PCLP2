#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

class ActivitateAgricola{
private:
    std::string tip,nume_planta;
    int luna,an,nr_h;
public:
    ActivitateAgricola(std::string tip,std::string nume_planta,int luna,int an,int nr_h):
    tip(tip),nume_planta(nume_planta),luna(luna),an(an),nr_h(nr_h){}
    
    virtual int get_luna(){
        return this->luna;
    }
    
    virtual int get_an(){
        return this->an;
    }
    
    virtual std::string get_nume_planta(){
        return this->nume_planta;
    }
    
    virtual int get_nr_h(){
        return this->nr_h;
    }
    
    virtual std::string get_tip(){
        return this->tip;
    }
    
    virtual int get_cant_recolta(){
        return 0;
    }
    
    virtual int get_nr_seminte(){
        return 0;
    }
    
    virtual void afisare()=0;
    
    ~ActivitateAgricola(){}
};

class Insamantare: public ActivitateAgricola{
private:
    int nr_seminte;
public:
    Insamantare(std::string tip,std::string nume_planta,int luna,int an,int nr_h,int nr_seminte):
    ActivitateAgricola(tip,nume_planta,luna,an,nr_h),nr_seminte(nr_seminte){}
    
    void afisare(){
        std::cout<<this->get_tip()<<"\n"<<this->get_luna()<<"."<<this->get_an()<<":"<<this->get_nume_planta()<<", Cantitate seminte:"<<this->nr_seminte<<"\n";
    }
    
    int get_nr_seminte(){
        return this->nr_seminte;
    }
    
    ~Insamantare(){}
};

class Recolta: public ActivitateAgricola{
private:
    int cant_recolta;
public:
    Recolta(std::string tip,std::string nume_planta,int luna,int an,int nr_h,int cant_recolta):
    ActivitateAgricola(tip,nume_planta,luna,an,nr_h),cant_recolta(cant_recolta){}
    
    int get_cant_recolta(){
        return this->cant_recolta;
    }
    
    void afisare(){
        std::cout<<this->get_tip()<<"\n"<<this->get_luna()<<"."<<this->get_an()<<":"<<this->get_nume_planta()<<", Cantitate recoltata:"<<this->cant_recolta<<"\n";
    }
    
    ~Recolta(){}
};

bool compare_recolta(ActivitateAgricola * l, ActivitateAgricola * r){
    if(l->get_cant_recolta()<r->get_cant_recolta())
        return true;
    else 
        return false;
}
    
bool compare_seminte(ActivitateAgricola *l, ActivitateAgricola*r){
    if(l->get_nr_seminte()<r->get_nr_seminte())
        return true;
    else 
        return false;
}

class DosarAgricol{
private:
    std::string nume_fermier;
    std::vector <ActivitateAgricola*> vec;
public:
    DosarAgricol(std::string nume_fermier):
    nume_fermier(nume_fermier){}
    
    void vec_add(ActivitateAgricola *a){
        vec.push_back(a);
    }
    
    void test1(){
        std::cout<<this->nume_fermier<<"\n";
        for(int i=0;i<vec.size();i++)
            vec[i]->afisare();
    }
    
    void test2(){
        for(int j=2022;j<=2023;j++){
            int nr_insamantari=0,kg_recoltate=0;
            for(int i=0;i<vec.size();i++){
                if(vec[i]->get_tip()=="Insamantare" && vec[i]->get_an()==j){
                    nr_insamantari++;
                }
                else if(vec[i]->get_tip()=="Recolta" && vec[i]->get_an()==j){
                    kg_recoltate=kg_recoltate+vec[i]->get_cant_recolta();
                }
            }
            std::cout<<j<<": "<<"nr insamantari="<<nr_insamantari<<", kg recoltate="<<kg_recoltate<<"\n";
        }
    }
    
    void test3(){
        int nr_recolte=0,nr_insamantari=0,nr_h_insamantate=0;
        int cantitate_recoltata=0,cantitate_seminte=0;
        for(int i=0;i<vec.size();i++){
            if(vec[i]->get_tip()=="Recolta"){
                nr_recolte++;
                cantitate_recoltata=cantitate_recoltata+vec[i]->get_cant_recolta();
            }
            else if(vec[i]->get_tip()=="Insamantare"){
                nr_insamantari++;
                nr_h_insamantate=nr_h_insamantate+vec[i]->get_nr_h();
                cantitate_seminte=cantitate_seminte+vec[i]->get_nr_seminte();
            }
        }
        std::cout<<"Performanta:"<<nr_recolte-nr_insamantari+nr_h_insamantate<<"\nEficienta:";
        std::cout<<std::fixed<<std::setprecision(2)<<cantitate_recoltata*1.0/cantitate_seminte<<"\n";
    }
    
    void test4(){
        std::sort(vec.begin(),vec.end(),compare_seminte);
        std::cout<<"Insamantari:\n";
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_nr_seminte()!=0)
                std::cout<<vec[i]->get_luna()<<"."<<vec[i]->get_an()<<":"<<vec[i]->get_nr_seminte()<<"\n";
        std::sort(vec.begin(),vec.end(),compare_recolta);
        std::cout<<"\nRecolte:\n";
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_cant_recolta()!=0)
                std::cout<<vec[i]->get_luna()<<"."<<vec[i]->get_an()<<":"<<vec[i]->get_cant_recolta()<<"\n";
    }
    
    ~DosarAgricol(){}
};

int main(){
    int test,nr_evenimente,temp_nr_h,temp_luna,temp_an,temp_nr_seminte,temp_cant_recolta;
    std::string temp_nume_fermier,temp_nume_planta,temp_tip;
    
    std::cin>>test;
    std::getline(std::cin>>std::ws, temp_nume_fermier);
    
    DosarAgricol dosar(temp_nume_fermier);
    
    std::cin>>nr_evenimente;
    for(int i=0;i<nr_evenimente;i++){
        std::cin>>temp_nume_planta>>temp_nr_h>>temp_luna>>temp_an>>temp_tip;
        if(temp_tip=="Insamantare"){
            std::cin>>temp_nr_seminte;
            dosar.vec_add(new Insamantare(temp_tip,temp_nume_planta,temp_luna,temp_an,temp_nr_h,temp_nr_seminte));
        }
        if(temp_tip=="Recolta"){
            std::cin>>temp_cant_recolta;
            dosar.vec_add(new Recolta(temp_tip,temp_nume_planta,temp_luna,temp_an,temp_nr_h,temp_cant_recolta));
        }
    }
    
    if(test==1){
        dosar.test1();
    }
    
    else if(test==2){
        dosar.test2();
    }
    
    else if(test==3){
        dosar.test3();
    }
    
    else{
        dosar.test4();
    }
    
    return 0;
}
