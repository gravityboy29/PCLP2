#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class PlatitorTaxe{
protected:
    std::string tip,nume;
    int suma_incasata,suma_netaxabila;
public:
    PlatitorTaxe(std::string tip,std::string nume,int suma_incasata,int suma_netaxabila):
    tip(tip),nume(nume),suma_incasata(suma_incasata),suma_netaxabila(suma_netaxabila){}
    
    std::string get_tip(){
        return this->tip;
    }
    std::string get_nume(){
        return this->nume;
    }
    
    void afisare(){
        std::cout<<nume<<"\n"<<suma_incasata<<"\n";
    }
    virtual void taxe_de_baza(double taxe)=0;
    double venituri_netaxabile(){
        return (double)suma_netaxabila/suma_incasata*100;
    }
};

class PersoanaFizica: public PlatitorTaxe{
public:
    PersoanaFizica(std::string tip,std::string nume,int suma_incasata,int suma_netaxabila):
    PlatitorTaxe(tip,nume,suma_incasata,suma_netaxabila){}
    
    void taxe_de_baza(double taxe){
        double t=(suma_incasata-suma_netaxabila)*(1-(100-taxe)/100.00);
        std::cout<<nume<<"\n"<<t<<"\n";
    }
};

class Firma: public PlatitorTaxe{
public:
    Firma(std::string tip,std::string nume,int suma_incasata,int suma_netaxabila):
    PlatitorTaxe(tip,nume,suma_incasata,suma_netaxabila){}
    
    void taxe_de_baza(double taxe){
        double t=(suma_incasata-suma_netaxabila)*(1-(100-taxe)/100.00);
        std::cout<<nume<<"\n"<<t<<"\n";
    }
};

class AgentieAdministrareFiscala{
private:
    std::vector <PlatitorTaxe*> vec;
public:
    AgentieAdministrareFiscala(){}
    
    void vec_add(PlatitorTaxe *a){
        vec.push_back(a);
    }
    
    void test1(){
        for(int i=0;i<vec.size();i++)
            vec[i]->afisare();
    }
    
    void test2(int taxe_p,int taxe_f){
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_tip()=="Persoana Fizica")
                vec[i]->taxe_de_baza(taxe_p);
            else if(vec[i]->get_tip()=="Firma")
                vec[i]->taxe_de_baza(taxe_f);
    }
    
    void test3(){
        bool k=false;
        for(int i=0;i<vec.size();i++)
            if(vec[i]->venituri_netaxabile()>20){
                std::cout<<vec[i]->get_nume()<<"\n";
                std::cout<<std::fixed<<std::setprecision(2)<<vec[i]->venituri_netaxabile()<<"\n";
                k=true;
            }
        if(!k)
            std::cout<<"Nicio potentiala frauda detectata\n";
    }
};

int main(){
    int test,nr_entitati,temp_suma_incasata,temp_suma_netaxabila;
    std::string temp_tip,temp_nume;
    
    AgentieAdministrareFiscala agentie;
    
    std::cin>>test>>nr_entitati;
    for(int i=0;i<nr_entitati;i++){
        std::getline(std::cin>>std::ws, temp_tip);
        std::getline(std::cin>>std::ws, temp_nume);
        std::cin>>temp_suma_incasata>>temp_suma_netaxabila;
        if(temp_tip=="Persoana Fizica")
            agentie.vec_add(new PersoanaFizica(temp_tip,temp_nume,temp_suma_incasata,temp_suma_netaxabila));
        else if(temp_tip=="Firma")
            agentie.vec_add(new Firma(temp_tip,temp_nume,temp_suma_incasata,temp_suma_netaxabila));
    }
    
    if(test==1){
        agentie.test1();
    }
    else if(test==2){
        double temp_taxe_p,temp_taxe_f;
        std::cin>>temp_taxe_p>>temp_taxe_f;
        agentie.test2(temp_taxe_p,temp_taxe_f);
    }
    else if(test==3){
        agentie.test3();
    }
    else{
        
    }
    
    return 0;
}
