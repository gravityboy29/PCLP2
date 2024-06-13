#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

class JocVideo{
protected:
    std::string nume;
    int zi,luna,an,nr_note;
    int *note;
public:
    JocVideo(std::string nume,int zi,int luna,int an,int nr_note,int* note):
    nume(nume),zi(zi),luna(luna),an(an),nr_note(nr_note){
        this->note=new int[nr_note];
        for(int i=0;i<nr_note;i++)
            this->note[i]=note[i];
    }
    
    std::string get_nume(){
        return this->nume;
    }
    
    float nota_medie(){
        int s=0;
        for(int i=0;i<nr_note;i++)
            s+=note[i];
        return s*1.0/nr_note;
    }
    
    virtual void display()=0;
    //virtual void get_playtime(int a,float b)=0;
    
    ~JocVideo(){}
};

class JocSinglePlayer: public JocVideo{
private:
    int nr_nivele;
public:
    JocSinglePlayer(std::string nume,int zi,int luna,int an,int nr_note,int* note,int nr_nivele):
    JocVideo(nume,zi,luna,an,nr_note,note),nr_nivele(nr_nivele){}
    
    void display(){
        std::cout<<"singleplayer: "<<nume<<" - "<<zi<<" "<<luna<<" "<<an<<" - "<<nr_nivele<<"\n";
    }
    ~JocSinglePlayer(){}
};

class JocMultiPlayer: public JocVideo{
private:
    int nr_meciuri;
public:
    JocMultiPlayer(std::string nume,int zi,int luna,int an,int nr_note,int* note,int nr_meciuri):
    JocVideo(nume,zi,luna,an,nr_note,note),nr_meciuri(nr_meciuri){}
    
    void display(){
        std::cout<<"multiplayer: "<<nume<<" - "<<zi<<" "<<luna<<" "<<an<<" - "<<nr_meciuri<<"\n";
    }
    
    ~JocMultiPlayer(){}
};

class JocVideoHandler{
private:
    std::vector <JocVideo*> vec;
public:
    JocVideoHandler(){}
    
    void vec_add(JocVideo *a){
        vec.push_back(a);
    }
    
    void test1(){
        for(int i=0;i<vec.size();i++)
            vec[i]->display();
    }
    
    void test2(){
        float max=0, k=0;
        for(int i=0;i<vec.size();i++)
            if(vec[i]->nota_medie()>max){
                max=vec[i]->nota_medie(); k=i;
            }
        std::cout<<vec[k]->get_nume()<<": ";
        std::cout<<std::fixed<<std::setprecision(2)<<vec[k]->nota_medie()<<"\n";
    }
    
    ~JocVideoHandler(){}
};

int main(){
    int test,nr_jocuri,t_zi,t_luna,t_an,t_nr_note,t_nr_nivele,t_nr_meciuri;
    std::string t_nume,indicator;
    
    JocVideoHandler joc;
    
    std::cin>>nr_jocuri;
    for(int i=0;i<nr_jocuri;i++){
        std::getline(std::cin>>std::ws, t_nume);
        std::cin>>t_zi>>t_luna>>t_an>>t_nr_note;
        int *t_note=new int[t_nr_note];
        for(int j=0;j<t_nr_note;j++)
            std::cin>>t_note[j];
        std::cin>>indicator;
        if(indicator=="singleplayer"){
            std::cin>>t_nr_nivele;
            joc.vec_add(new JocSinglePlayer(t_nume,t_zi,t_luna,t_an,t_nr_note,t_note,t_nr_nivele));
        }
        else if(indicator=="multiplayer"){
            std::cin>>t_nr_meciuri;
            joc.vec_add(new JocMultiPlayer(t_nume,t_zi,t_luna,t_an,t_nr_note,t_note,t_nr_meciuri));
        }
    }
    std::cin>>test;
    
    if(test==1){
        joc.test1();
    }
    else if(test==2){
        joc.test2();
    }
    //mi e lene
    
    return 0;
}
