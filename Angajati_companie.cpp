#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Angajat{
private:
    std::string tip,nume;
    float salariu_brut;
    int zile_concediu;
public:
    Angajat(std::string tip,std::string nume,float salariu_brut,int zile_concediu):
    tip(tip),nume(nume),salariu_brut(salariu_brut),zile_concediu(zile_concediu){}
    
    virtual std::string get_tip(){
        return this->tip;
    }
    virtual std::string get_nume(){
        return this->nume;
    }
    virtual float get_salariu_brut(){
        return this->salariu_brut;
    }
    virtual int get_zile_concediu(){
        return this->zile_concediu;
    }
    
    void afisare(){
        std::cout<<get_tip()<<"\n"<<get_nume()<<":"<<get_salariu_brut()<<"\n";
        std::cout<<"\n";
    }
    virtual int calcul_plata()=0;
    virtual float calcul_salariu()=0;
    
    ~Angajat(){}
};

class PersoanaFizica: public Angajat{
private:
    int ore_lucrate;
public:
    PersoanaFizica(std::string tip,std::string nume,float salariu_brut,int zile_concediu,int ore_lucrate):
    Angajat(tip,nume,salariu_brut,zile_concediu),ore_lucrate(ore_lucrate){}
    
    int calcul_plata(){
        return get_salariu_brut()/(ore_lucrate*4);
    }
    
    float calcul_salariu(){
        return (100-42)/100.0*get_salariu_brut();
    }
    
    ~PersoanaFizica(){}
};

class PersoanaJuridica: public Angajat{
private:
    int zile_lucrate;
public:
    PersoanaJuridica(std::string tip,std::string nume,float salariu_brut,int zile_concediu,int zile_lucrate):
    Angajat(tip,nume,salariu_brut,zile_concediu),zile_lucrate(zile_lucrate){}
    
    int calcul_plata(){
        return get_salariu_brut()/(zile_lucrate*4*8);
    }
    
    float calcul_salariu(){
        return (100-10)/100.0*get_salariu_brut();
    }
    
    ~PersoanaJuridica(){}
};

bool comp(Angajat *l, Angajat *r){
    if(l->calcul_salariu()>r->calcul_salariu())
        return true;
    else
        return false;
}

class AdministrareAngajat{
private:
    std::vector <Angajat*> vec;
public:
    AdministrareAngajat(){}
    
    void vec_add(Angajat *a){
        vec.push_back(a);
    }
    
    void test1(){
        for(int i=0;i<vec.size();i++)
            vec[i]->afisare();
    }
    void test2(){
        for(int i=0;i<vec.size();i++){
            std::cout<<vec[i]->get_nume()<<":"<<vec[i]->calcul_plata()<<" lei/h\n";
        }
    }
    void test3(){
        for(int i=0;i<vec.size();i++)
            std::cout<<vec[i]->get_nume()<<":"<<vec[i]->get_salariu_brut()<<"-"<<int(vec[i]->calcul_salariu())<<"\n";
    }
    void test4(){
        std::sort(vec.begin(),vec.end(),comp);
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_tip()=="Persoana fizica")
                std::cout<<vec[i]->get_nume()<<":"<<vec[i]->get_salariu_brut()<<"\n";
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_tip()=="Persoana juridica")
                std::cout<<vec[i]->get_nume()<<":"<<vec[i]->get_salariu_brut()<<"\n";
    }
    
    ~AdministrareAngajat(){}
};

int main(){
    int test,nr_angajati,temp_zile_concediu;
    std::string temp_tip,temp_nume;
    float temp_salariu_brut,temp_ore_lucrate,temp_zile_lucrate;
    
    AdministrareAngajat angajat;
    
    std::cin>>test>>nr_angajati;
    for(int i=0;i<nr_angajati;i++){
        std::getline(std::cin>>std::ws, temp_tip);
        std::getline(std::cin>>std::ws, temp_nume);
        std::cin>>temp_salariu_brut>>temp_zile_concediu;
        if(temp_tip=="Persoana fizica"){
            std::cin>>temp_ore_lucrate;
            angajat.vec_add(new PersoanaFizica(temp_tip,temp_nume,temp_salariu_brut,temp_zile_concediu,temp_ore_lucrate));
        }
        else if(temp_tip=="Persoana juridica"){
            std::cin>>temp_zile_lucrate;
            angajat.vec_add(new PersoanaJuridica(temp_tip,temp_nume,temp_salariu_brut,temp_zile_concediu,temp_zile_lucrate));
        }
    }
    
    if(test==1){
        angajat.test1();
    }
    else if(test==2){
        angajat.test2();
    }
    else if(test==3){
        angajat.test3();
    }
    else{
        angajat.test4();
    }
    
    return 0;
}
