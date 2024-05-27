#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

class Participant{
protected:
    std::string nume_participant;
    float rezultat;
public:
    Participant(std::string nume_participant, float rezultat):
    nume_participant(nume_participant), rezultat(rezultat){}
    
    std::string get_nume_participant(){
        return this->nume_participant;
    }
    float get_rezultat(){
        return this->rezultat;
    }
};

bool comp_scor(Participant *l, Participant *r){
    if(l->get_rezultat()>r->get_rezultat())
        return true;
    else
        return false;
}

bool comp_timp(Participant *l, Participant *r){
    if(l->get_rezultat()<r->get_rezultat())
        return true;
    else
        return false;
}

class ProbaSportiva{
protected:
    std::string tip,nume_proba;
    std::vector <Participant*> vec_p;
public:
   ProbaSportiva(std::string tip, std::string nume_proba):
   tip(tip),nume_proba(nume_proba){}
   
    void vec_p_add(Participant *a){
        vec_p.push_back(a);
    }
   
   std::string get_tip(){
       return this->tip;
   }
   
   std::string get_nume_proba(){
       return this->nume_proba;
   }
   
   std::vector <Participant*>& get_participant(){
       return vec_p;
   }
   
   virtual void afisare()=0;
   
   void rezultat_mediu(){
       float rez_med=0;
       int k=0;
       for(int i=0;i<vec_p.size();i++){
            rez_med+=vec_p[i]->get_rezultat(); k++;
       }
        std::cout<<"Rezultat mediu la "<<nume_proba<<": "<<rez_med/k<<"\n";
   }
   
   float record_mondial(){
       if(tip=="s"){
           float max=0;
           for(int i=0;i<vec_p.size();i++){
               if(vec_p[i]->get_rezultat()>max)
                    max=vec_p[i]->get_rezultat();
           }
           return max;
       }
       else{
           float min=vec_p[0]->get_rezultat();
           for(int i=1;i<vec_p.size();i++){
               if(vec_p[i]->get_rezultat()<min)
                    min=vec_p[i]->get_rezultat();
           }
           return min;
       }
   }
};

class ProbaScor:public ProbaSportiva{
public:
   ProbaScor(std::string tip, std::string nume_proba):
   ProbaSportiva(tip,nume_proba){}
   
   void afisare(){
       for(int i=0;i<vec_p.size();i++)
            std::cout<<vec_p[i]->get_nume_participant()<<" "<<vec_p[i]->get_rezultat()<<"\n";
   }
};

class ProbaTimp:public ProbaSportiva{
public:
   ProbaTimp(std::string tip, std::string nume_proba):
   ProbaSportiva(tip,nume_proba){}
   
   void afisare(){
       for(int i=0;i<vec_p.size();i++)
            std::cout<<vec_p[i]->get_nume_participant()<<" "<<vec_p[i]->get_rezultat()<<"\n";
   }
};

int main(){
    int test,nr_probe,temp_nr_participanti;
    std::string temp_tip,temp_nume_proba,temp_nume_participant;
    float temp_rezultat;
    
    std::vector <ProbaSportiva*> vec;
    
    std::cin>>nr_probe;
    for(int i=0;i<nr_probe;i++){
        std::cin>>temp_tip>>temp_nume_proba>>temp_nr_participanti;
        ProbaSportiva *proba=nullptr;
        if(temp_tip=="t")
            proba=new ProbaTimp(temp_tip,temp_nume_proba);
        else if(temp_tip=="s")
            proba=new ProbaScor(temp_tip,temp_nume_proba);
        for(int j=0;j<temp_nr_participanti;j++){
            std::cin>>temp_nume_participant>>temp_rezultat;
            proba->vec_p_add(new Participant(temp_nume_participant,temp_rezultat));
        }
        vec.push_back(proba);
    }
    std::cin>>test;
    
    if(test==1){
        for(int i=0;i<vec.size();i++){
            std::cout<<vec[i]->get_nume_proba()<<"\n";
            vec[i]->afisare();
        }
    }
    
    else if(test==2){
        for(int i=0;i<vec.size();i++){
            vec[i]->rezultat_mediu();
        }
    }
    
    else if(test==3){
        float record;
        for(int i=0;i<nr_probe;i++){
            std::cin>>record;
            if((vec[i]->record_mondial()>record && vec[i]->get_tip()=="s")||
            (vec[i]->record_mondial()<record && vec[i]->get_tip()=="t"))
                std::cout<<"Un nou record mondial la "<<vec[i]->get_nume_proba()<<"!\n";
        }
    }
    
    else if(test==4){
        std::string nume_competitie;
        std::cin>>nume_competitie;
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_nume_proba()==nume_competitie){
                if(vec[i]->get_tip()=="s")
                    std::sort(vec[i]->get_participant().begin(),vec[i]->get_participant().end(),comp_scor);
                else if(vec[i]->get_tip()=="t")
                    std::sort(vec[i]->get_participant().begin(),vec[i]->get_participant().end(),comp_timp);
                vec[i]->afisare();
            }
    }
    
    else{
        
    }
    return 0;
}
