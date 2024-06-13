#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Vehicul{
protected:
    int masa;
    std::string marca;
public:
    Vehicul(int masa,std::string marca):
    masa(masa),marca(marca){}
    virtual void display()=0;
    virtual float viteza_maxima()=0;
    virtual int masa_aditionala()=0;
    virtual void adauga_bagaj(int masa_bagaj)=0;
    
    ~Vehicul(){}
};

class Motocicleta: public Vehicul{
private:
    std::string tip;
public:
    Motocicleta(int masa,std::string marca,std::string tip):
    Vehicul(masa,marca),tip(tip){}
    
    void display(){
        std::cout<<"motocicleta "<<masa<<" "<<marca<<" "<<tip<<"\n";
    }
    
    int masa_aditionala(){
        return 70;
    }
    
    float viteza_maxima(){
        return 300000.0/(masa+masa_aditionala());
    }
    
    void adauga_bagaj(int masa_bagaj){
        std::cout<<masa+masa_aditionala()<<"\n";
    }
    
    ~Motocicleta(){}
};

class Masina: public Vehicul{
protected:
    int nr_pasageri,capacitate_portbagaj;
public:
    Masina(int masa,std::string marca,int nr_pasageri,int capacitate_portbagaj):
    Vehicul(masa,marca),nr_pasageri(nr_pasageri),capacitate_portbagaj(capacitate_portbagaj){}
    
    void display(){
        std::cout<<"masina "<<masa<<" "<<marca<<" "<<nr_pasageri<<" "<<capacitate_portbagaj<<"\n";
    }
    
    int masa_aditionala(){
        return (nr_pasageri+1)*70;
    }
    
     float viteza_maxima(){
        return 300000.0/(masa+masa_aditionala());
    }
    void adauga_bagaj(int masa_bagaj){
        if(masa_bagaj<=capacitate_portbagaj)
            std::cout<<masa+masa_aditionala()+masa_bagaj<<"\n";
        else
            std::cout<<masa+masa_aditionala()+capacitate_portbagaj<<"\n";
    }
    
    ~Masina(){}
};

class MasinaElectrica: public Masina{
private:
    int masa_baterie;
public:
    MasinaElectrica(int masa,std::string marca,int nr_pasageri,int capacitate_portbagaj,int masa_baterie):
    Masina(masa,marca,nr_pasageri,capacitate_portbagaj),masa_baterie(masa_baterie){}
    
    void display(){
        std::cout<<"masina electrica "<<masa<<" "<<marca<<" "<<nr_pasageri<<" "<<capacitate_portbagaj<<" "<<masa_baterie<<"\n";
    }
    
    int masa_aditionala(){
        return (nr_pasageri+1)*70+masa_baterie;
    }
    
     float viteza_maxima(){
        return 300000.0/(masa+masa_aditionala());
    }
    
    void adauga_bagaj(int masa_bagaj){
        if(masa_bagaj<=capacitate_portbagaj)
            std::cout<<masa+masa_aditionala()+masa_bagaj<<"\n";
        else
            std::cout<<masa+masa_aditionala()+capacitate_portbagaj<<"\n";
    }
    
    ~MasinaElectrica(){}
};

bool comp(Vehicul *l, Vehicul *r){
    if(l->viteza_maxima()>r->viteza_maxima())
        return true;
    else
        return false;
}

int main(){
    int test,nr_vehicule,t_masa,t_nr_pasageri,t_capacitate_portbagaj,t_masa_baterie;
    std::string t_marca,indicator,t_tip;
    
    std::vector <Vehicul*> vec;
    
    std::cin>>nr_vehicule;
    for(int i=0;i<nr_vehicule;i++){
        std::cin>>t_masa>>t_marca>>indicator;
        if(indicator=="moto"){
            std::cin>>t_tip;
            vec.push_back(new Motocicleta(t_masa,t_marca,t_tip));
        }
        else if(indicator=="auto"){
            std::cin>>t_nr_pasageri>>t_capacitate_portbagaj;
            vec.push_back(new Masina(t_masa,t_marca,t_nr_pasageri,t_capacitate_portbagaj));
        }
        else if(indicator=="electric"){
            std::cin>>t_nr_pasageri>>t_capacitate_portbagaj>>t_masa_baterie;
            vec.push_back(new MasinaElectrica(t_masa,t_marca,t_nr_pasageri,t_capacitate_portbagaj,t_masa_baterie));
        }
    }
    std::cin>>test;
    
    if(test==1){
        for(int i=0;i<nr_vehicule;i++)
            vec[i]->display();
    }
    else if(test==2){
        for(int i=0;i<nr_vehicule;i++)
            std::cout<<vec[i]->masa_aditionala()<<"\n";
    }
    else if(test==3){
        for(int i=0;i<nr_vehicule;i++)
            std::cout<<vec[i]->viteza_maxima()<<"\n";
    }
    else if(test==4){
        int index,masa_bagaj;
        std::cin>>index>>masa_bagaj;
        for(int i=0;i<nr_vehicule;i++)
            if(index==i)
                vec[i]->adauga_bagaj(masa_bagaj);
    }
    else{
        std::sort(vec.begin(),vec.end(),comp);
        for(int i=0;i<nr_vehicule;i++)
            vec[i]->display();
    }
    
    return 0;
}
