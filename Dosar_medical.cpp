#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class EvenimentMedical{
private:
    std::string tip,sectie;
    int luna,an;
public:
    EvenimentMedical(std::string tip,int luna,int an,std::string sectie):
    tip(tip),luna(luna),an(an),sectie(sectie){}
    
    virtual std::string get_tip(){
        return this->tip;
    }
    virtual int get_luna(){
        return this->luna;
    }
    virtual int get_an(){
        return this->an;
    }
    virtual std::string get_sectie(){
        return this->sectie;
    }
    virtual int get_nr_zile(){
        return 0;
    }
    virtual std::string get_diagnostic(){
        return "";
    }
    
    virtual void afisare()=0;
    
    ~EvenimentMedical(){}
};

class Consultatie: public EvenimentMedical{
private:
    std::string diagnostic;
public:
    Consultatie(std::string tip,int luna,int an,std::string sectie,std::string diagnostic):
    EvenimentMedical(tip,luna,an,sectie),diagnostic(diagnostic){}
    
    std::string get_diagnostic(){
        return this->diagnostic;
    }
    
    void afisare(){
        std::cout<<get_tip()<<"\n";
        std::cout<<get_luna()<<"."<<get_an()<<","<<get_sectie()<<":"<<diagnostic<<"\n";
    }
    
    ~Consultatie(){}
};

class Internare: public EvenimentMedical{
private:
    int nr_zile;
public:
    Internare(std::string tip,int luna,int an,std::string sectie,int nr_zile):
    EvenimentMedical(tip,luna,an,sectie),nr_zile(nr_zile){}
    
    int get_nr_zile(){
        return this->nr_zile;
    }
    
    void afisare(){
        std::cout<<get_tip()<<"\n";
        std::cout<<get_luna()<<"."<<get_an()<<","<<get_sectie()<<":"<<nr_zile<<"\n";
    }
    
    ~Internare(){}
};

bool compare(EvenimentMedical *l, EvenimentMedical *r){
    if(l->get_nr_zile()>r->get_nr_zile())
        return true;
    else
        return false;
}

class DosarMedical{
private:
    std::string nume;
    int nr_comorbiditati;
    std::vector <EvenimentMedical*> vec;
public:
    DosarMedical(std::string nume,int nr_comorbiditati):
    nume(nume),nr_comorbiditati(nr_comorbiditati){}
    
    void vec_add(EvenimentMedical *a){
        vec.push_back(a);
    }
    
    void test1(){
        std::cout<<nume<<"\n";
        for(int i=0;i<vec.size();i++)
            vec[i]->afisare();
    }
    
    void test2(){
        int zile_internare, consultatii;
        for(int j=2022;j<=2023;j++){
            zile_internare=0; consultatii=0;
            for(int i=0;i<vec.size();i++){
                if(vec[i]->get_tip()=="Internare" && vec[i]->get_an()==j)
                    zile_internare+=vec[i]->get_nr_zile();
                else if(vec[i]->get_tip()=="Consultatie" && vec[i]->get_an()==j)
                    consultatii++;
            }
            std::cout<<j<<": zile internare="<<zile_internare<<", consultatii="<<consultatii<<"\n";
        }
    }
    
    void test3(){
        int nr_internari=0,nr_zile;
        for(int i=0;i<vec.size();i++){
            if((vec[i]->get_an()==2022 && vec[i]->get_luna()==12) ||
            (vec[i]->get_an()==2023 && vec[i]->get_luna()>=1 && vec[i]->get_luna()<=5)){
                if(vec[i]->get_tip()=="Internare"){
                    nr_internari++;
                    nr_zile=vec[i]->get_nr_zile();
                }
            }
            
            if(vec[i]->get_diagnostic()=="Bolnav")
                nr_comorbiditati++;
        }
        std::cout<<nr_internari+nr_zile+nr_comorbiditati<<"\n";
    }
    
    void test4(){
        std::sort(vec.begin(),vec.end(),compare);
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_nr_zile()!=0)
                std::cout<<vec[i]->get_luna()<<"."<<vec[i]->get_an()<<":"<<vec[i]->get_sectie()<<":"<<vec[i]->get_nr_zile()<<"\n";
    }
    
    ~DosarMedical(){}
};

int main(){
    std::string temp_nume,temp_sectie,temp_tip,temp_diagnostic;
    int temp_nr_comorbiditati,nr_evenimente,temp_luna,temp_an,temp_nr_zile,test;
    
    std::cin>>nr_evenimente;
    std::getline(std::cin>>std::ws, temp_nume);
    std::cin>>temp_nr_comorbiditati;
    
    DosarMedical dosar(temp_nume,temp_nr_comorbiditati);
    
    for(int i=0;i<nr_evenimente;i++){
        std::cin>>temp_an>>temp_luna;
        std::getline(std::cin>>std::ws, temp_sectie);
        std::cin>>temp_tip;
        if(temp_tip=="Consultatie"){
            std::cin>>temp_diagnostic;
            dosar.vec_add(new Consultatie(temp_tip,temp_luna,temp_an,temp_sectie,temp_diagnostic));
        }
        else if(temp_tip=="Internare"){
            std::cin>>temp_nr_zile;
            dosar.vec_add(new Internare(temp_tip,temp_luna,temp_an,temp_sectie,temp_nr_zile));
        }
    }
    std::cin>>test;
    
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
