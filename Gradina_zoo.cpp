#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Pasare{
protected:
    std::string nume;
    int dimensiune;
public:
    Pasare(std::string nume,int dimensiune):
    nume(nume),dimensiune(dimensiune){}
    
    int get_dimensiune(){
        return this->dimensiune;
    }
    std::string get_nume(){
        return this->nume;
    }
    virtual int get_batai_pe_minut(){
        return 0;
    }
    virtual std::string get_culoare(){
        return "";
    }
    
    virtual void afisare()=0;
    virtual float suprafata()=0;
};

class Zburatoare: public Pasare{
private:
    int batai_pe_minut;
public:
    Zburatoare(std::string nume,int dimensiune,int batai_pe_minut):
    Pasare(nume,dimensiune),batai_pe_minut(batai_pe_minut){}
    
    int get_batai_pe_minut(){
        return this->batai_pe_minut;
    }
    
    void afisare(){
        std::cout<<nume<<" "<<dimensiune<<" "<<batai_pe_minut<<"\n";
    }
    float suprafata(){
        return dimensiune*110*batai_pe_minut/100;
    }
};

class Nezburatoare: public Pasare{
private:
    std::string culoare;
public:
    Nezburatoare(std::string nume,int dimensiune,std::string culoare):
    Pasare(nume,dimensiune),culoare(culoare){}
    
    std::string get_culoare(){
        return this->culoare;
    }
    
    void afisare(){
        std::cout<<nume<<" "<<dimensiune<<" "<<culoare<<"\n";
    }
    float suprafata(){
        return dimensiune*30;
    }
};

bool comp(Pasare *l, Pasare *r){
    if(l->suprafata()<r->suprafata())
        return true;
    else
        return false;
}

int main(){
    int nr_pasari,temp_dimensiune,temp_batai_pe_minut=0,test;
    std::string tip,temp_nume,temp_culoare;
    
    std::vector <Pasare*> vec;
    
    std::cin>>nr_pasari;
    for(int i=0;i<nr_pasari;i++){
        std::cin>>tip>>temp_nume>>temp_dimensiune;
        if(tip=="z"){
            std::cin>>temp_batai_pe_minut;
            vec.push_back(new Zburatoare(temp_nume,temp_dimensiune,temp_batai_pe_minut));
        }
        else if(tip=="n"){
            std::cin>>temp_culoare;
            vec.push_back(new Nezburatoare(temp_nume,temp_dimensiune,temp_culoare));
        }
    }
    std::cin>>test;
    
    if(test==1){
        for(int i=0;i<nr_pasari;i++)
            vec[i]->afisare();
    }
    else if(test==2){
        std::string c; 
        int dim;
        std::cin>>c>>dim;
        for(int i=0;i<nr_pasari;i++)
            if(vec[i]->get_dimensiune()>=dim)
                if(c=="z" && vec[i]->get_batai_pe_minut()!=0)
                    vec[i]->afisare();
                else if(c=="n" && vec[i]->get_culoare()!="")
                    vec[i]->afisare();
    }
    else if(test==3){
        for(int i=0;i<nr_pasari;i++)
            std::cout<<vec[i]->get_nume()<<" "<<vec[i]->suprafata()<<"\n";
    }
    else if(test==4){
        std::sort(vec.begin(),vec.end(),comp);
        for(int i=0;i<nr_pasari;i++)
            vec[i]->afisare();
    }
    else{
        float Sz=0,Sn=0;
        for(int i=0;i<nr_pasari;i++){
            if(vec[i]->get_batai_pe_minut()!=0)
                Sz+=vec[i]->suprafata();
            else if(vec[i]->get_culoare()!="")
                Sn+=vec[i]->suprafata();
        }
        if(Sz>Sn)
            std::cout<<Sz<<"\n";
        else
            std::cout<<Sn<<"\n";
    }
    
    return 0;
}
