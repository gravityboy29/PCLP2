#include <iostream>
#include <vector>
#include <string>

class Angajat{
protected:
    std::string nume,functie;
    float salariu_baza,procent_taxe_salariu;
public:
    Angajat(std::string nume,float salariu_baza,std::string functie):
    nume(nume),salariu_baza(salariu_baza),functie(functie){}
    
    std::string get_nume(){
        return this->nume;
    }
    float get_salariu_baza(){
        return this->salariu_baza;
    }
    std::string get_functie(){
        return this->functie;
    }
    
    void afisare(){
        std::cout<<nume<<"\n"<<functie<<"\n";
    }
    
    virtual float get_salariu_net(float procent_taxe_salariu)=0;
    
    virtual float get_salariu_brut()=0;
    
    void marire_salariu(float procent_marire){
        float salariu_marit=salariu_baza*(100+procent_marire)/100;
        salariu_baza=salariu_marit;
    }
    virtual ~Angajat(){
        std::cout<<"Destructor Angajat\n";
    }
};

class Analist: public Angajat{
public:
    Analist(std::string nume,float salariu_baza,std::string functie):
    Angajat(nume,salariu_baza,functie){}
    
    float get_salariu_brut(){
        return salariu_baza;
    }
    
    float get_salariu_net(float procent_taxe_salariu){
        return salariu_baza*(100-procent_taxe_salariu)/100;
    }
    
    ~Analist(){
        std::cout<<"Destructor Analist\n";
    }
};

class Programator: public Analist{
protected:
    float procent_deducere_salariu_it=10;
public:
    Programator(std::string nume,float salariu_baza,std::string functie):
    Analist(nume,salariu_baza,functie){}
    
    float get_salariu_brut(){
        return salariu_baza;
    }
    
    float get_salariu_net(float procent_taxe_salariu){
        return salariu_baza*(100-procent_taxe_salariu+procent_deducere_salariu_it)/100;
    }
    
    ~Programator(){
        std::cout<<"Destructor Programator\n";
    }
};

class LiderEchipaProgramare: public Programator{
protected:
    float bonus_vechime_functie=500;
    int vechime_functie;
public:
    LiderEchipaProgramare(std::string nume,float salariu_baza,std::string functie,int vechime_functie):
    Programator(nume,salariu_baza,functie),vechime_functie(vechime_functie){}
    
    float get_salariu_brut(){
        return salariu_baza+bonus_vechime_functie*vechime_functie;
    }
    
    float get_salariu_net(float procent_taxe_salariu){
        return get_salariu_brut()*(100-procent_taxe_salariu+procent_deducere_salariu_it)/100;
    }
    
    ~LiderEchipaProgramare(){
        std::cout<<"Destructor LiderEchipaProgramare\n";
    }
};

class FirmaProgramare{
private:
    std::vector <Angajat*> vec;
public:
    FirmaProgramare(){}
    
    void vec_add(Angajat *a){
        vec.push_back(a);
    }
    
    void afiseaza_angajati(){
        for(int i=0;i<vec.size();i++)
            vec[i]->afisare();
    }
    
    void calcularea_salariilor(){
        for(int i=0;i<vec.size();i++){
            std::cout<<vec[i]->get_nume()<<"\n";
            std::cout<<"Salariu brut: "<<vec[i]->get_salariu_brut()<<"\n";
            std::cout<<"Salariu Net: "<<vec[i]->get_salariu_net(40)<<"\n";
        }
    }
    
    void mareste_salarii(float a,float p,float l){
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_functie()=="Analist"){
                std::cout<<vec[i]->get_nume()<<"\n";
                std::cout<<"Salariu de baza vechi: "<<vec[i]->get_salariu_baza()<<"\n";
                vec[i]->marire_salariu(a);
                std::cout<<"Salariu de baza nou: "<<vec[i]->get_salariu_baza()<<"\n";
            }
            else if(vec[i]->get_functie()=="Programator"){
                std::cout<<vec[i]->get_nume()<<"\n";
                std::cout<<"Salariu de baza vechi: "<<vec[i]->get_salariu_baza()<<"\n";
                vec[i]->marire_salariu(p);
                std::cout<<"Salariu de baza nou: "<<vec[i]->get_salariu_baza()<<"\n";
            }
            else if(vec[i]->get_functie()=="LiderEchipaProgramare"){
                std::cout<<vec[i]->get_nume()<<"\n";
                std::cout<<"Salariu de baza vechi: "<<vec[i]->get_salariu_baza()<<"\n";
                vec[i]->marire_salariu(l);
                std::cout<<"Salariu de baza nou: "<<vec[i]->get_salariu_baza()<<"\n";            }
    }
    
    void promoveaza(std::string nume,std::string functie){
        for(int i=0;i<vec.size();i++){
            if(vec[i]->get_nume()==nume){
                float salariu_p=vec[i]->get_salariu_baza();
                delete vec[i];
                if(functie=="Analist")
                    vec[i]=new Analist(nume,salariu_p,functie);
                else if(functie=="Programator")
                    vec[i]=new Programator(nume,salariu_p,functie);
                else if(functie=="LiderEchipaProgramare")
                    vec[i]=new LiderEchipaProgramare(nume,salariu_p,functie,0);
            }
        }
    }
    
    ~FirmaProgramare(){}
};

int main(){
    int test,nr_angajati,temp_vechime_functie;
    std::string temp_nume,temp_functie;
    float temp_salariu_baza;
    
    FirmaProgramare firma;
    
    std::cin>>nr_angajati;
    for(int i=0;i<nr_angajati;i++){
        std::getline(std::cin>>std::ws, temp_nume);
        std::getline(std::cin>>std::ws, temp_functie);
        std::cin>>temp_salariu_baza;
        if(temp_functie=="Analist")
            firma.vec_add(new Analist(temp_nume,temp_salariu_baza,temp_functie));
        else if(temp_functie=="Programator")
            firma.vec_add(new Programator(temp_nume,temp_salariu_baza,temp_functie));
        else if(temp_functie=="LiderEchipaProgramare"){
            std::cin>>temp_vechime_functie;
            firma.vec_add(new LiderEchipaProgramare(temp_nume,temp_salariu_baza,temp_functie,temp_vechime_functie));
        }
    }
    std::cin>>test;
    
    if(test==1){
        firma.afiseaza_angajati();
    }
    else if(test==2){
        firma.calcularea_salariilor();
    }
    else if(test==3){
        std::string functie;
        int a,p,l;
        for(int i=0;i<3;i++){
            std::cin>>functie;
            if(functie=="Analist")
                std::cin>>a;
            else if(functie=="Programator")
                std::cin>>p;
            else if(functie=="LiderEchipaProgramare")
                std::cin>>l;
        }
        firma.mareste_salarii(a,p,l);
    }
    else if(test==4){
        std::string nume,functie;
        std::getline(std::cin>>std::ws, nume);
        std::cin>>functie;
        firma.promoveaza(nume,functie);
        firma.afiseaza_angajati();
    }
    
    return 0;
}
