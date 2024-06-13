#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Fisier{
protected:
    std::string nume;
    int zi,luna,an;
public:
    Fisier(std::string nume,int zi,int luna,int an):
    nume(nume),zi(zi),luna(luna),an(an){}
    
    int get_zi(){
        return this->zi;
    }
    int get_luna(){
        return this->luna;
    }
    int get_an(){
        return this->an;
    }
    
    virtual void display()=0;
    virtual void get_size()=0;
    virtual float size()=0;
};

class FisierText: public Fisier{
private:
    std::string corp;
public:
    FisierText(std::string nume,int zi,int luna,int an,std::string corp):
    Fisier(nume,zi,luna,an),corp(corp){}
    
    void display(){
        std::cout<<"text "<<nume<<" "<<zi<<" "<<luna<<" "<<an<<" "<<corp<<"\n";
    }
    
    float size(){
        return corp.size()*8;
    }
    
    void get_size(){
        std::cout<<size()<<"\n";
    }
};

class FisierAudio: public Fisier{
private:
    int nr_esantioane;
    int *esantioane;
public:
    FisierAudio(std::string nume,int zi,int luna,int an,int nr_esantioane,int *esantioane):
    Fisier(nume,zi,luna,an),nr_esantioane(nr_esantioane){
        this->esantioane=new int[nr_esantioane];
        for(int i=0;i<nr_esantioane;i++)
            this->esantioane[i]=esantioane[i];
    }
    
    void display(){
        int i;
        std::cout<<"audio "<<nume<<" "<<zi<<" "<<luna<<" "<<an<<" ";
        for(i=0;i<nr_esantioane-1;i++)
            std::cout<<esantioane[i]<<" ";
        std::cout<<esantioane[i]<<"\n";
    }
    
    float size(){
        int s=0;
        for(int i=0;i<nr_esantioane;i++)
            s+=esantioane[i];
        return s*2;
    }
    
    void get_size(){
        std::cout<<size()<<"\n";
    }
};

bool comp(Fisier *l, Fisier *r){
    if(l->get_an()>r->get_an() ||
    (l->get_an()==r->get_an() && l->get_luna()>r->get_luna()) ||
    (l->get_an()==r->get_an() && l->get_luna()==r->get_luna() && l->get_zi()>r->get_zi()))
        return true;
    else
        return false;
}

bool comp_size(Fisier *l, Fisier *r){
    if(l->size()>r->size())
        return true;
    else
        return false;
}

class FileHandler{
private:
    std::vector <Fisier*> vec;
public:
    FileHandler(){}
    
    void vec_add(Fisier *a){
        vec.push_back(a);
    }
    
    void test1(){
        for(int i=0;i<vec.size();i++)
            vec[i]->display();
    }
    
    void test2(int zi,int luna, int an){
        for(int i=0;i<vec.size();i++)
            if(vec[i]->get_an()>an ||
            (vec[i]->get_an()==an && vec[i]->get_luna()>luna) ||
            (vec[i]->get_an()==an && vec[i]->get_luna()==luna && vec[i]->get_zi()>zi))
                vec[i]->display();
    }
    
    void test3(){
        std::sort(vec.begin(),vec.end(),comp);
        vec[0]->display();
        vec[vec.size()-1]->display();
    }
    
    void test4(){
        for(int i=0;i<vec.size();i++)
            vec[i]->get_size();
    }
    
    void test5(){
        std::sort(vec.begin(),vec.end(),comp_size);
        for(int i=0;i<vec.size();i++)
            vec[i]->display();
    }
};

int main(){
    int test,nr_fisiere,t_zi,t_luna,t_an,t_nr_esantioane,t_esantioane;
    std::string t_nume,indicator,t_corp;
    
    FileHandler fisier;
    
    std::cin>>nr_fisiere;
    for(int i=0;i<nr_fisiere;i++){
        std::cin>>t_nume>>t_zi>>t_luna>>t_an>>indicator;
        if(indicator=="text"){
            std::getline(std::cin>>std::ws, t_corp);
            fisier.vec_add(new FisierText(t_nume,t_zi,t_luna,t_an,t_corp));
        }
        else if(indicator=="audio"){
            std::cin>>t_nr_esantioane;
            int *t_esantioane=new int[t_nr_esantioane];
            for(int j=0;j<t_nr_esantioane;j++)
                std::cin>>t_esantioane[j];
            fisier.vec_add(new FisierAudio(t_nume,t_zi,t_luna,t_an,t_nr_esantioane,t_esantioane));
        }
    }
    std::cin>>test;
    if(test==1){
        fisier.test1();  
    }
    else if(test==2){
        int zi,luna,an;
        std::cin>>zi>>luna>>an;
        fisier.test2(zi,luna,an);
    }
    else if(test==3){
        fisier.test3();
    }
    else if(test==4){
        fisier.test4();
    }
    else{
        fisier.test5();
    }
    
    return 0;
}
