#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

class Proprietate{
protected:
    int pret,suprafata;
    std::string tip,locatie;
public:
    Proprietate(std::string tip,int pret,std::string locatie,int suprafata):
    tip(tip),pret(pret),locatie(locatie),suprafata(suprafata){}
    
    virtual int get_pret(){
        return this->pret;
    }
    virtual std::string get_tip(){
        return this->tip;
    }
    virtual std::string get_locatie(){
        return this->locatie;
    }
    virtual int get_suprafata(){
        return this->suprafata;
    }
    int get_nr_etaje(){
        return 0;
    }
    int get_dimensiune_terasa(){
        return 0;
    }
    
    virtual void afisare()=0;
    virtual int suprafata_totala()=0;
    virtual float pret_mp()=0;
    
    ~Proprietate(){}
};

class Casa: public Proprietate{
private:
    int nr_etaje;
public:
    Casa(std::string tip,int pret,std::string locatie,int suprafata,int nr_etaje):
    Proprietate(tip,pret,locatie,suprafata),nr_etaje(nr_etaje){}
    
    int get_nr_etaje(){
        return this->nr_etaje;
    }
    
    void afisare(){
        std::cout<<"Casa "<<pret<<" "<<locatie<<" "<<suprafata<<" "<<nr_etaje<<"\n";
    }
    
    int suprafata_totala(){
        return suprafata*nr_etaje;
    }
    
    float pret_mp(){
        return pret*1.0/suprafata_totala();
    }
    
    ~Casa(){}
};

class Apartament: public Proprietate{
private:
    int dimensiune_terasa;
public:
    Apartament(std::string tip,int pret,std::string locatie,int suprafata,int dimensiune_terasa):
    Proprietate(tip,pret,locatie,suprafata),dimensiune_terasa(dimensiune_terasa){}
    
    int get_dimensiune_terasa(){
        return this->dimensiune_terasa;
    }
    
    void afisare(){
        std::cout<<"Apartament "<<pret<<" "<<locatie<<" "<<suprafata<<" "<<dimensiune_terasa<<"\n";
    }
    
    int suprafata_totala(){
        return suprafata+dimensiune_terasa;
    }
    
    float pret_mp(){
        return pret*1.0/suprafata_totala();
    }
    
    ~Apartament(){}
};

bool comp_pret(Proprietate *l, Proprietate *r){
    if(l->pret_mp()<r->pret_mp())
        return true;
    else
        return false;
}

class GestiuneProprietate{
private:
    std::vector <Proprietate*> vec;
public:
    GestiuneProprietate(){}
    
    void vec_add(Proprietate *a){
        vec.push_back(a);
    }
    
    void test1(){
        for(int i=0;i<vec.size();i++)
            vec[i]->afisare();
    }
    
    void test2(){
        for(int i=0;i<vec.size();i++)
            std::cout<<vec[i]->suprafata_totala()<<"\n";
    }
    
    void test3(){
        for(int i=0;i<vec.size();i++)
            std::cout<<std::fixed<<std::setprecision(2)<<vec[i]->pret_mp()<<"\n";
    }
    
    void test4(){
        std::sort(vec.begin(),vec.end(),comp_pret);
        for(int i=0;i<vec.size();i++){
            vec[i]->afisare();
            std::cout<<std::fixed<<std::setprecision(2)<<vec[i]->pret_mp()<<"\n";
        }
    }
    
    void test5(std::string p1,int p2,std::string p3,int p4,int p5){
        
    }
};

int main(){
    int test,nr_proprietati,temp_pret,temp_suprafata,temp_nr_etaje,temp_dimensiune_terasa;
    std::string temp_tip,temp_locatie;
    
    GestiuneProprietate proprietate;
    
    std::cin>>nr_proprietati;
    for(int i=0;i<nr_proprietati;i++){
        std::cin>>temp_tip>>temp_pret>>temp_locatie>>temp_suprafata;
        if(temp_tip=="c"){
            std::cin>>temp_nr_etaje;
            proprietate.vec_add(new Casa(temp_tip,temp_pret,temp_locatie,temp_suprafata,temp_nr_etaje));
        }
        else if(temp_tip=="a"){
            std::cin>>temp_dimensiune_terasa;
            proprietate.vec_add(new Apartament(temp_tip,temp_pret,temp_locatie,temp_suprafata,temp_dimensiune_terasa));
        }
    }
    std::cin>>test;
    
    if(test==1){
        proprietate.test1();
    }
    else if(test==2){
        proprietate.test2();
    }
    else if(test==3){
        proprietate.test3();
    }
    else if(test==4){
        proprietate.test4();
    }
    else if(test==5){
        std::string p1,p3;
        int p2,p4,p5;
        std::cin>>p1>>p2>>p3>>p4>>p5;
        proprietate.test5(p1,p2,p3,p4,p5);
    }
    
    return 0;
}
