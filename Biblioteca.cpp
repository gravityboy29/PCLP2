#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

class Carte{
protected:
    std::string titlu,gen;
    int zi,luna,an,nr_recenzii;
    int *recenzii;
public:
    Carte(std::string titlu,int zi,int luna,int an,std::string gen,int nr_recenzii,int* recenzii):
    titlu(titlu),zi(zi),luna(luna),an(an),gen(gen),nr_recenzii(nr_recenzii){
        this->recenzii=new int[nr_recenzii];
        for(int i=0;i<nr_recenzii;i++){
            this->recenzii[i]=recenzii[i];
        }
    }
    
    std::string get_titlu(){
        return this->titlu;
    }
    int get_zi(){
        return this->zi;
    }
    int get_luna(){
        return this->luna;
    }
    int get_an(){
        return this->an;
    }
    std::string get_gen(){
        return this->gen;
    }
    
    virtual void display()=0;
    float medie_recenzii(){
        int s=0;
        for(int i=0;i<nr_recenzii;i++)
            s+=recenzii[i];
        return s*1.0/nr_recenzii;
    }
    // virtual void nr_pagini(int a,int b)=0;
    
    ~Carte(){}
};

class CarteFictiune: public Carte{
private:
    int nr_capitole;
public:
    CarteFictiune(std::string titlu,int zi,int luna,int an,std::string gen,int nr_recenzii,int* recenzii,int nr_capitole):
    Carte(titlu,zi,luna,an,gen,nr_recenzii,recenzii),nr_capitole(nr_capitole){}
    
    void display(){
        std::cout<<"fictiune: "<<titlu<<" - "<<zi<<" "<<luna<<" "<<an<<" - "<<nr_capitole<<"\n";
    }
    
    ~CarteFictiune(){}
};

class CarteNonFictiune: public Carte{
private:
    int nr_pagini;
public:
    CarteNonFictiune(std::string titlu,int zi,int luna,int an,std::string gen,int nr_recenzii,int* recenzii,int nr_pagini):
    Carte(titlu,zi,luna,an,gen,nr_recenzii,recenzii),nr_pagini(nr_pagini){}
    
    void display(){
        std::cout<<"nonfictiune: "<<titlu<<" - "<<zi<<" "<<luna<<" "<<an<<" - "<<nr_pagini<<"\n";
    }
    
    ~CarteNonFictiune(){}
};

bool comp(Carte *l, Carte *r){
    if(l->get_an()>r->get_an() ||
    (l->get_an()==r->get_an() && l->get_luna()>r->get_luna()) ||
    (l->get_an()==r->get_an() && l->get_luna()==r->get_luna() && l->get_zi()>r->get_zi()))
        return true;
    else
        return false;
}

class Biblioteca{
private:
    std::vector <Carte*> vec;
public:
    Biblioteca(){}
    
    void vec_add(Carte *a){
        vec.push_back(a);
    }
    
    void test1(){
        for(int i=0;i<vec.size();i++)
            vec[i]->display();
    }
    
    void test2(){
        float max=0,k=0;
        for(int i=0;i<vec.size();i++)
            if(vec[i]->medie_recenzii()>max){
                max=vec[i]->medie_recenzii();
                k=i;
            }
        std::cout<<vec[k]->get_titlu()<<": ";
        std::cout<<std::fixed<<std::setprecision(2)<<max<<"\n";
    }
    
    void test3(int zi,int luna,int an){
        for(int i=0;i<vec.size();i++){
            if((vec[i]->get_an()>an) ||
            (vec[i]->get_an()==an && vec[i]->get_luna()>luna) || 
            (vec[i]->get_an()==an && vec[i]->get_luna()==luna && vec[i]->get_zi()>zi))
                std::cout<<vec[i]->get_titlu()<<": "<<vec[i]->get_gen()<<"\n";
        }
    }
    
    void test4(){
        std::sort(vec.begin(),vec.end(),comp);
        vec[0]->display();
        vec[vec.size()-1]->display();
    }
    
    ~Biblioteca(){}
};

int main(){
    int test,nr_carti,t_zi,t_luna,t_an,t_nr_recenzii,t_nr_capitole,t_nr_pagini;
    std::string t_titlu,t_gen;
    
    Biblioteca biblioteca;
    
    std::cin>>nr_carti;
    for(int i=0;i<nr_carti;i++){
        std::getline(std::cin>>std::ws, t_titlu);
        std::cin>>t_zi>>t_luna>>t_an>>t_nr_recenzii;
        int *t_recenzii=new int[t_nr_recenzii];
        for(int j=0;j<t_nr_recenzii;j++)
            std::cin>>t_recenzii[j];
        std::cin>>t_gen;
        if(t_gen=="fictiune"){
            std::cin>>t_nr_capitole;
            biblioteca.vec_add(new CarteFictiune(t_titlu,t_zi,t_luna,t_an,t_gen,t_nr_recenzii,t_recenzii,t_nr_capitole));
        }
        else if(t_gen=="nonfictiune"){
            std::cin>>t_nr_pagini;
            biblioteca.vec_add(new CarteNonFictiune(t_titlu,t_zi,t_luna,t_an,t_gen,t_nr_recenzii,t_recenzii,t_nr_pagini));
        }
    }
    std::cin>>test;
    
    if(test==1){
        biblioteca.test1();
    }
    else if(test==2){
        biblioteca.test2();
    }
    else if(test==3){
        int zi,luna,an;
        std::cin>>zi>>luna>>an;
        biblioteca.test3(zi,luna,an);
    }
    else if(test==4){
        biblioteca.test4();
    }
    else{
       //mi e lene 
    }
    
    return 0;
}
