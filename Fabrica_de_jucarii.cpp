#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

class Jucarie{
protected:
    std::string tematica,nume;
public:
    Jucarie(std::string tematica,std::string nume):
    tematica(tematica),nume(nume){}
    
    std::string get_tematica(){
        return this->tematica;
    }
    
    virtual void afisare()=0;
    virtual int varsta()=0;
    virtual void afisare_varsta()=0;
    
    ~Jucarie(){}
};

class Action_figure: public Jucarie{
private:
    int inaltime,latime,lungime;
public:
    Action_figure(std::string tematica,std::string nume,int inaltime,int latime,int lungime):
    Jucarie(tematica,nume),inaltime(inaltime),latime(latime),lungime(lungime){}
    
    void afisare(){
        std::cout<<"Action_figure "<<tematica<<" "<<nume<<" "<<inaltime<<" "<<latime<<" "<<lungime<<"\n";
    }
    
    int varsta(){
        if(inaltime<latime && inaltime<lungime)
            return 10/inaltime;
        else if(latime<inaltime && latime<lungime)
            return 10/latime;
        else
            return 10/lungime;
    }
    
    void afisare_varsta(){
        std::cout<<"Action_figure"<<" "<<nume<<" "<<varsta()<<"\n";
    }
    
    ~Action_figure(){}
};

class Puzzle: public Jucarie{
private:
    int nr_piese,latime,lungime;
public:
    Puzzle(std::string tematica,std::string nume,int nr_piese,int latime,int lungime):
    Jucarie(tematica,nume),nr_piese(nr_piese),latime(latime),lungime(lungime){}
    
    void afisare(){
        std::cout<<"Puzzle "<<tematica<<" "<<nume<<" "<<nr_piese<<" "<<latime<<" "<<lungime<<"\n";
    }
    
    int varsta(){
        float lungime_piese, latime_piese;
        lungime_piese=lungime/sqrt(nr_piese);
        latime_piese=latime/sqrt(nr_piese);
        if(lungime_piese<=latime_piese)
            return 10/lungime_piese;
        else
            return 10/latime_piese;
    }
    
    void afisare_varsta(){
        std::cout<<"Puzzle"<<" "<<nume<<" "<<varsta()<<"\n";
    }
    
    ~Puzzle(){}
};

bool comp(Jucarie *l, Jucarie *r){
    if(l->varsta()<r->varsta())
        return true;
    else
        return false;
}

int main(){
    int test,nr_jucarii,temp_inaltime,temp_latime,temp_lungime,temp_nr_piese;
    std::string tip,temp_tematica,temp_nume;
    
    std::vector <Jucarie*> vec;
    
    std::cin>>nr_jucarii;
    for(int i=0;i<nr_jucarii;i++){
        std::cin>>tip>>temp_tematica>>temp_nume;
        if(tip=="a"){
            std::cin>>temp_inaltime>>temp_latime>>temp_lungime;
            vec.push_back(new Action_figure(temp_tematica,temp_nume,temp_inaltime,temp_latime,temp_lungime));
        }
        else if(tip=="p"){
            std::cin>>temp_nr_piese>>temp_latime>>temp_lungime;
            vec.push_back(new Puzzle(temp_tematica,temp_nume,temp_nr_piese,temp_latime,temp_lungime));
        }
    }
    std::cin>>test;
    
    if(test==1){
        for(int i=0;i<nr_jucarii;i++)
            vec[i]->afisare();
    }
    
    else if(test==2){
        std::string tematica;
        std::cin>>tematica;
        for(int i=0;i<nr_jucarii;i++)
            if(vec[i]->get_tematica()==tematica)
                vec[i]->afisare();
    }
    
    else if(test==3){
        for(int i=0;i<nr_jucarii;i++)
            vec[i]->afisare_varsta();
    }
    
    else{
        std::sort(vec.begin(),vec.end(),comp);
        for(int i=0;i<nr_jucarii;i++)
            vec[i]->afisare();
    }
    
    return 0;
}
