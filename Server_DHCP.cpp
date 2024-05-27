#include <iostream>
#include <vector>
#include <algorithm>

class Dispozitiv{
private:
    int id,ip;
public:
    Dispozitiv(int id,int ip):id(id),ip(ip=0){}
    
    int get_id(){
        return this->id;
    }
    int get_ip(){
        return this->ip;
    }
    void set_ip(int ip_nou){
        this->ip=ip_nou;
    }
    
    void afisare(){
        std::cout<<id<<" "<<ip<<"\n";
    }
    
    void generare_ip(){
        int n,elem_lipsa=1;
        std::cin>>n;
        std::vector<int> pool(n);
        for(int i=0;i<n;i++){
            std::cin>>pool[i];
        }
        for(int i=0;i<n;i++){
            if(elem_lipsa==pool[i])
                elem_lipsa++;
            else
                break;
        }
        pool.push_back(elem_lipsa);
        std::sort(pool.begin(),pool.end());
        for(int i=0;i<=n;i++)
            std::cout<<pool[i]<<" ";
    }
    
    void eliminare_ip(){
        int n,pool_elim;
        std::cin>>n;
        std::vector<int> pool(n);
        for(int i=0;i<n;i++)
            std::cin>>pool[i];
        std::cin>>pool_elim;
        for(int i=0;i<n;i++)
            if(pool[i]==pool_elim)
                for(int j=i;j<n-1;j++)
                    pool[j]=pool[j+1];
        for(int i=0;i<n-1;i++)
            std::cout<<pool[i]<<" ";
    }
};

int main(){
    int test,temp_id,temp_ip;
    
    std::vector <Dispozitiv*> vec;
    Dispozitiv dispozitiv(temp_id,temp_ip);
    
    do{
        std::cin>>test;
        if(test==1){
            std::cin>>temp_id;
            vec.push_back(new Dispozitiv(temp_id,temp_ip));
        }
        else if(test==2){
            for(int i=0;i<vec.size();i++)
                vec[i]->afisare();
        }
        else if(test==3){
            dispozitiv.generare_ip();
        }
        else if(test==4){
            int id_dispozitiv,k;
            std::cin>>id_dispozitiv;
            for(int i=0;i<vec.size();i++)
                if(id_dispozitiv==vec[i]->get_id()){
                    k++;
                    vec[i]->set_ip(k);
                }
        }
        else if(test==5){
            dispozitiv.eliminare_ip();
        }
        else if(test==6){
            
        }
    }while(test!=-1);

    return 0;
}
