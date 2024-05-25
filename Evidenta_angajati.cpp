#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class Angajat{
private:
    std::string nume;
    std::string departament;
public:
    Angajat(std::string nume, std::string departament):
    nume(nume),departament(departament){}
    
    std::string get_nume(){
        return this->nume;
    }
    
    std::string get_departament(){
        return this->departament;
    }
    
    virtual void afisare()=0;
    virtual int salariu_brut()=0;
    virtual float rentabilitate_angajat()=0;
};

class Salariat: public Angajat{
private:
    int norma,vechime;
    float salariu_net; 
public:
    Salariat(std::string nume, std::string departament, int norma, int vechime, float salariu_net):
    Angajat(nume,departament),norma(norma),vechime(vechime),salariu_net(salariu_net){}
    
    void afisare(){
        std::cout<<this->get_nume()<<" "<<this->norma<<" "<<this->vechime<<" "<<this->salariu_net<<"\n";
    }
    
    int salariu_brut(){
        if(get_departament()=="IT")
            return salariu_net*12/(1-0.35);
        else
            return salariu_net*12/(1-0.45);
    }
    
    float rentabilitate_angajat(){
        return norma*(250-20-vechime/3)*1.0/salariu_brut();
    }
};

class Colaborator: public Angajat{
private:
    float onorariu,nr_prestari_anuale;
public:
    Colaborator(std::string nume, std::string departament, float onorariu, float nr_prestari_anuale):
    Angajat(nume,departament),onorariu(onorariu),nr_prestari_anuale(nr_prestari_anuale){}
    
    void afisare(){
        std::cout<<this->get_nume()<<" "<<this->onorariu<<" "<<this->nr_prestari_anuale<<"\n";
    }
    
    int salariu_brut(){
        if(get_departament()=="IT")
            return onorariu*nr_prestari_anuale/(1-0.35);
        else
            return onorariu*nr_prestari_anuale/(1-0.45);
    }
    
    float rentabilitate_angajat(){
        return 0;
    }
};

int main(){
    int test,nr_angajati,temp_norma,temp_vechime;
    std::string tip,temp_nume,temp_departament;
    float temp_salariu_net,temp_onorariu,temp_prestari_anuale;
    
    std::vector <Angajat*> vec;
    
    std::cin>>nr_angajati;
    for(int i=0;i<nr_angajati;i++){
        std::cin>>tip>>temp_nume>>temp_departament;
        if(tip=="salariat"){
            std::cin>>temp_norma>>temp_vechime>>temp_salariu_net;
            vec.push_back(new Salariat(temp_nume,temp_departament,temp_norma,temp_vechime,temp_salariu_net));
        }
        if(tip=="colaborator"){
            std::cin>>temp_onorariu>>temp_prestari_anuale;
            vec.push_back(new Colaborator(temp_nume,temp_departament,temp_onorariu,temp_prestari_anuale));
        }
    }
    std::cin>>test;
    
    if(test==1){
        std::string nume_dep;
        std::cin>>nume_dep;
        for(int i=0;i<nr_angajati;i++)
            if(nume_dep==vec[i]->get_departament())
                vec[i]->afisare();
    }
    
    else if(test==2){
        std::string nume;
        std::cin>>nume;
        for(int i=0;i<nr_angajati;i++)
            if(nume==vec[i]->get_nume())
                std::cout<<vec[i]->salariu_brut()<<"\n";
    }
    
    else if(test==3){
        float max=-1.00,x;
        for(int i=0;i<nr_angajati;i++)
            if(vec[i]->rentabilitate_angajat()>max){
                max=vec[i]->rentabilitate_angajat();
                x=i;
            }
        std::cout<<vec[x]->get_nume()<<"\n";
    }
    
    else{
        float s=0,x=0;
        std::string departament;
        std::cin>>departament;
        for(int i=0;i<nr_angajati;i++)
            if(vec[i]->get_departament()==departament){
                s=s+vec[i]->salariu_brut();
                x++;
            }
        std::cout<<std::fixed<<std::setprecision(2)<<s/x;
    }
    
    return 0;
}
