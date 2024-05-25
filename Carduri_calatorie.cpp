#include <iostream>
#include <vector>

class Card_calatorie{
private:
    int id;
    char tip;
public:
    Card_calatorie(int id, char tip):id(id),tip(tip){}
    
    int get_id(){
        return this->id;
    }
    
    char get_tip(){
        return this->tip;
    }
    
    virtual void afisare()=0;
    virtual void validare_calatorie(int, int)=0;
    virtual void incarcare(int)=0;
    virtual int get_nr()=0;
};

class Card_autobuz: public Card_calatorie{
private:
    int sold,moment_validare=0;
public:
    Card_autobuz(int id, char tip, int sold):Card_calatorie(id,tip),sold(sold){}
    
    int get_nr(){
        return this->sold;
    }
    
    void afisare(){
        std::cout<<this->get_id()<<" "<<this->get_tip()<<" "<<this->sold<<" "<<moment_validare<<"\n";
    }
    
    void incarcare(int sold_incarcare){
        this->sold+=sold_incarcare;
    }
    
    void validare_calatorie(int id_val, int mom_val){
        if(this->sold<3){
            std::cout<<"Sold insuficient"<<"\n";
        }
        else if(mom_val-moment_validare>90 && this->sold>=3){
            this->sold-=3;
            this->moment_validare=mom_val;
        }
    }
};

class Card_metrou: public Card_calatorie{
private:
    int nr_calatorii,moment_validare=0;
public:
    Card_metrou(int id, char tip, int nr_calatorii):Card_calatorie(id,tip),nr_calatorii(nr_calatorii){}
    
    int get_nr(){
        return this->nr_calatorii;
    }
    
    void afisare(){
        std::cout<<this->get_id()<<" "<<this->get_tip()<<" "<<this->nr_calatorii<<" "<<moment_validare<<"\n";
    }
    
    void incarcare(int nr_incarcare){
        this->nr_calatorii+=nr_incarcare;
    }
    void validare_calatorie(int id_val, int mom_val){
        if(this->nr_calatorii<1){
            std::cout<<"Numar calatorii insuficient"<<"\n";
        }
        else if(mom_val-moment_validare>90 && this->nr_calatorii>=1){
            this->nr_calatorii-=1;
            this->moment_validare=mom_val;
        }
    }
};

int main(){
    char temp_tip;
    int temp_id,temp_sold,temp_nr_calatorii,test=0,nr_carduri;
    
    std::vector <Card_calatorie*> vec;
    
    std::cin>>nr_carduri;
    for(int i=0;i<nr_carduri;i++){
        std::cin>>temp_tip;
        std::cin>>temp_id;
        if(temp_tip=='a'){
            std::cin>>temp_sold;
            vec.push_back(new Card_autobuz(temp_id,temp_tip,temp_sold));
        }
        else if(temp_tip=='m'){
            std::cin>>temp_nr_calatorii;
            vec.push_back(new Card_metrou(temp_id,temp_tip,temp_nr_calatorii));
        }
    }
    while(test!=5){
        std::cin>>test;
        if(test==1){
            for(int i=0;i<nr_carduri;i++){
                vec[i]->afisare();
            }
        }
        
        else if(test==2){
            int id_incarcare,sold_incarcare;
            std::cin>>id_incarcare>>sold_incarcare;
            for(int i=0;i<nr_carduri;i++)
                if(id_incarcare==vec[i]->get_id())
                    vec[i]->incarcare(sold_incarcare);
        }
            
        else if(test==3){
            int id_val,mom_val;
            std::cin>>id_val>>mom_val;
            for(int i=0;i<nr_carduri;i++)
                if(id_val==vec[i]->get_id())
                    vec[i]->validare_calatorie(id_val,mom_val);
        }
        
        else if(test==4){
            int id_1,id_2,suma;
            std::cin>>id_1>>id_2>>suma;
            for(int i=0;i<nr_carduri;i++){
                if(id_1==vec[i]->get_id())
                    for(int j=0;j<nr_carduri;j++)
                        if(id_2==vec[j]->get_id()){
                            if(vec[i]->get_tip()==vec[j]->get_tip() && vec[i]->get_nr()>=suma){
                                vec[i]->incarcare(-suma);
                                vec[j]->incarcare(suma);
                            }
                            else
                                std::cout<<"Transfer nereusit\n";
                        }
            }
        }
    }
    return 0;
}
