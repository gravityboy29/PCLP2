#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

class Publicatie{
private:
    std::string titlu,tip;
    int nr_autori,an,nr_citari;
public:
    Publicatie(std::string titlu,int nr_autori,int an,int nr_citari,std::string tip):
    titlu(titlu),nr_autori(nr_autori),an(an),nr_citari(nr_citari),tip(tip){}
    
    virtual std::string get_titlu(){
        return this->titlu;
    }
    virtual int get_nr_autori(){
        return this->nr_autori;
    }
    virtual int get_an(){
        return this->an;
    }
    virtual int get_nr_citari(){
        return this->nr_citari;
    }
    
    virtual void afisare()=0;
    virtual float punctaj_anual()=0;
    
    ~Publicatie(){}
};

class Conferinta: public Publicatie{
private:
    int isi;
public:
    Conferinta(std::string titlu,int nr_autori,int an,int nr_citari,std::string tip,int isi):
    Publicatie(titlu,nr_autori,an,nr_citari,tip),isi(isi){}
    
    void afisare(){
        if(isi==1)
            std::cout<<get_titlu()<<", "<<get_nr_autori()<<", "<<get_an()<<", "<<get_nr_citari()<<", "<<"ISI\n";
        else
            std::cout<<get_titlu()<<", "<<get_nr_autori()<<", "<<get_an()<<", "<<get_nr_citari()<<", "<<"non-ISI\n";
    }
    
    float punctaj_anual(){
        float pct=0;
        if(isi==1)
            pct+=0.75;
        else
            pct+=0.25;
        return pct;
    }
    
    ~Conferinta(){}
};

class Revista: public Publicatie{
private:
    int q;
public:
    Revista(std::string titlu,int nr_autori,int an,int nr_citari,std::string tip,int q):
    Publicatie(titlu,nr_autori,an,nr_citari,tip),q(q){}
    
    void afisare(){
        std::cout<<get_titlu()<<", "<<get_nr_autori()<<", "<<get_an()<<", "<<get_nr_citari()<<", "<<"Q"<<q<<"\n";
    }
    
    float punctaj_anual(){
        if(q==1)
            return 20.0/get_nr_autori();
        else if(q==2)
            return 10.0/get_nr_autori();
        else
            return 5.0/get_nr_autori();
    }
    
    ~Revista(){}
};

bool comp(Publicatie *l, Publicatie *r){
    if(l->get_nr_citari()>r->get_nr_citari())
        return true;
    else
        return false;
}

class Profil{
private:
    std::string nume;
    std::vector <Publicatie*> vec;
public:
    Profil(std::string nume):
    nume(nume){}
    
    void vec_add(Publicatie *a){
        vec.push_back(a);
    }
    
    void test1(){
        std::cout<<nume<<"\n";
        for(int i=0;i<vec.size();i++)
            vec[i]->afisare();
    }
    void test2(){
        for(int j=2023;j>=2021;j--){
            float punctaj=0;
            for(int i=0;i<vec.size();i++)
                if(vec[i]->get_an()==j){
                    punctaj+=vec[i]->punctaj_anual();
                }
            std::cout<<std::fixed<<std::setprecision(2)<<punctaj<<"\n";
        }
    }
    void test3(){
        int k=0;
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_nr_citari()>=10)
                k++;
        std::cout<<k<<"\n";
    }
    void test4(){
        int x,k;
        std::sort(vec.begin(),vec.end(),comp);
        for(int i=1;i<vec.size();i++){
            k=-1;
            for(int j=0;j<vec.size();j++){
                if(vec[j]->get_nr_citari()>=vec[i]->get_nr_citari())
                    x=vec[i]->get_nr_citari(); k++;
            }
            if(k==vec[i]->get_nr_citari())
                break;
        }
        std::cout<<k<<"\n";
    }
    
    ~Profil(){}
};

int main(){
    std::string temp_nume,temp_titlu,temp_tip;
    int nr_publicatii,temp_nr_autori,temp_an,temp_nr_citari,temp_isi,temp_q,test;
    
    std::getline(std::cin>>std::ws, temp_nume);
    std::cin>>nr_publicatii;
    
    Profil profil(temp_nume);
    
    for(int i=0;i<nr_publicatii;i++){
        std::getline(std::cin>>std::ws, temp_titlu);
        std::cin>>temp_nr_autori>>temp_an>>temp_nr_citari>>temp_tip;
        if(temp_tip=="conferinta"){
            std::cin>>temp_isi;
            profil.vec_add(new Conferinta(temp_titlu,temp_nr_autori,temp_an,temp_nr_citari,temp_tip,temp_isi));
        }
        else if(temp_tip=="revista"){
            std::cin>>temp_q;
            profil.vec_add(new Revista(temp_titlu,temp_nr_autori,temp_an,temp_nr_citari,temp_tip,temp_q));
        }
    }
    std::cin>>test;
    
    if(test==1){
        profil.test1();
    }
    else if(test==2){
        profil.test2();
    }
    else if(test==3){
        profil.test3();
    }
    else{
        profil.test4();
    }
    
    return 0;
}
