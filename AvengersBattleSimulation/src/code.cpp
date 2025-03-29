#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
class QNS;


queue<QNS> suits;
int max_power=5000;

class QNS{
    private:
        int p,d,e,h;
    public:
        QNS(int p,int d,int e,int h): p(min(5000,p)),d(d),e(e),h(h){};
        QNS(): p(1000),d(500),e(300),h(0){};
        QNS(const QNS& q): p(q.p), d(q.d), e(q.e), h(q.h) {};
        void operator +(QNS& q){
            p=min(p+q.get_energyStorage(),max_power);
            d+=q.get_durability();;
            e+=q.get_powerLevel();
        };
        bool operator -(int X){
            d-=X;
            e+=X;
            h+=X;
            if (d<=0){
                return false;
            }
            return true;
        };
        void operator *(int X){
            p=min(max_power,p+(p*X)/100);
            e+=5*X;
            h+=X;
        }
        void operator /(int X){
            d+=X;
            h=max(0,h-X);
        }
        bool operator ==(QNS& q){  
            if (this->d==q.d && this->p==q.p) return true;
            return false;
        }
        bool operator <(QNS& q){
            if (this->p+this->d<q.p+q.d) return true;
            return false;
        }
        int get_powerLevel(){
            return p;
        }
        int get_durability(){
            return d;
        }
        int get_energyStorage(){
            return e;
        }
        int get_heatLevel(){
            return h;
        }
        void set_powerLevel(int p){
            this->p=p;
        }
        void set_durability(int d){
            this->d=d;
        }
        void set_energyStorage(int e){
            this->e=e;
        }
        void set_heatLevel(int h){
            this->h=h;
        }
        void boostPower(int factor){
            (*this)*factor;
        }
        void boostPower(QNS otherSuit){ 
            (*this)+otherSuit;
        }
};
class Avenger{
    private:
        string name;
        QNS suit;
        int attackStrength;
    public:
        Avenger(string avName, QNS avSuit, int strength):name(avName),suit(avSuit),attackStrength(strength){};
        void attack(Avenger& enemy){
            *(enemy.get_QNS())-attackStrength;
        }
        bool upgradeSuit(){
            if (!suits.empty()){
                QNS temp=QNS(suits.front());
                suits.pop();
                suit+temp;
                return true;
            }
            return false;
        }
        void repair(int x){
            suit/x;
        }
        void printStatus(){
            cout<<name<<" "<<suit.get_powerLevel()<<" "<<suit.get_durability()<<" "<<suit.get_energyStorage()<<" "<<suit.get_heatLevel()<<endl;
        }
        string get_name(){
            return name;
        }
        QNS* get_QNS(){
            return &suit;
        }
        int get_attackstrength(){
            return attackStrength;
        }
};
class Battle{
    private:
        vector<Avenger*> Avengers;
        vector<Avenger*> enemies;
        vector<string> battleLog;
    public:
        Avenger* search(string name){
            for (auto i:Avengers){
                if (i->get_name()==name){
                    return i;
                }
            }
            for (auto i:enemies){
                if (i->get_name()==name){
                    return i;
                }
            }
            return NULL;
        }

        void startBattle(){
            string s="start";
            while (s!="End"){
                cin>>s;
                if (s=="Attack"){
                    string av1,av2;
                    cin>>av1>>av2;
                    Avenger* avenger1=search(av1);
                    Avenger *avenger2=search(av2);
                    if (avenger1 && avenger2 && avenger1->get_QNS()->get_durability()>0 && 
                        avenger1->get_QNS()->get_heatLevel()<=500 && avenger2->get_QNS()->get_durability()>0){
                        push_battlelog((string)(av1+" attacks "+av2));
                        avenger1->attack(*avenger2);
                        if (avenger2->get_QNS()->get_durability()<=0){
                            push_battlelog(av2+" suit destroyed");
                        }
                        else if (avenger2->get_QNS()->get_heatLevel()>500){
                            push_battlelog(av2+" suit overheated");
                        }
                    }
                } 
                else if (s=="Repair"){
                    string av;
                    int x;
                    cin>>av>>x;
                    Avenger *avenger=search(av);
                    avenger->repair(x);
                    push_battlelog(av+" repaired");
                }
                else if (s=="BoostPowerByFactor"){
                    string av;
                    int y;
                    cin>>av>>y;
                    Avenger *avenger=search(av);
                    avenger->get_QNS()->boostPower(y);
                    push_battlelog(av+" boosted");
                    if (avenger->get_QNS()->get_heatLevel()>500){
                        push_battlelog(av+" suit overheated");
                    }
                }
                else if (s=="BoostPower"){
                    string av;
                    int p,d,e,h;
                    cin>>av>>p>>d>>e>>h;
                    Avenger *avenger=search(av);
                    avenger->get_QNS()->boostPower(QNS(p,d,e,h));
                    push_battlelog(av+" boosted");
                    // if (avenger->get_QNS()->get_heatLevel()>500){
                    //     push_battlelog(av+" suit overheated");
                    // }
                }
                else if (s=="AvengerStatus"){
                    string av;
                    cin>>av;
                    Avenger *avenger=search(av);
                    avenger->printStatus();
                }
                else if (s=="Upgrade"){
                    string av;
                    cin>>av;
                    Avenger *avenger=search(av);
                    if (avenger->get_QNS()->get_durability()>0 && avenger->upgradeSuit()){
                        push_battlelog(av+" upgraded");
                    }
                    else{
                        push_battlelog(av+" upgrade Fail");
                    }
                }
                else if (s=="PrintBattleLog"){
                    printBattleLog();
                }
                else if (s=="BattleStatus"){
                    int res=Result();
                    if (res==1){
                        cout<<"heroes are winning"<<endl;
                    }
                    else if (res==-1){
                        cout<<"enemies are winning"<<endl;
                    }
                    else{
                        cout<<"tie"<<endl;
                    }
                }
            }            
        }
        void printBattleLog(){
            for (auto i:battleLog){
                cout<<i<<endl;
            }
        }
        int Result(){
            int avengers_score=0,enemy_score=0;
            for (auto i:Avengers){
                if (i->get_QNS()->get_durability()>0){
                    avengers_score+=i->get_QNS()->get_durability()+i->get_QNS()->get_powerLevel();
                }
            }
            for (auto i:enemies){
                if (i->get_QNS()->get_durability()>0){
                    enemy_score+=i->get_QNS()->get_durability()+i->get_QNS()->get_powerLevel();
                }
            }
            if (avengers_score>enemy_score) return 1;
            else if (enemy_score>avengers_score) return -1;
            else return 0;
        }
        void push_battlelog(string log){
            battleLog.push_back(log);
        }
        void push_avenger(Avenger* av){
            Avengers.push_back(av);
        }
        void push_enemy(Avenger* en){
            enemies.push_back(en);
        }
};

int main(){
    int k,n,m;
    cin>>k>>n>>m;
    Battle battle;
    for (int i=0;i<k;i++){
        int p,d,e,h;
        cin>>p>>d>>e>>h;
        suits.push(QNS(p,d,e,h));
    }
    for (int i=0;i<n;i++){
        string name;
        int attack;
        cin>>name>>attack;
        if (!suits.empty()){
            QNS temp=QNS(suits.front());
            suits.pop();
            Avenger* av=new Avenger(name,temp,attack);
            battle.push_avenger(av);          
        }
        else{
            cout<<name<<" is out of fight"<<endl;
        }
    }
    for (int i=0;i<m;i++){
        string name;
        int attack;
        cin>>name>>attack;
        if (!suits.empty()){
            QNS temp=QNS(suits.front());
            suits.pop();
            Avenger* ene=new Avenger(name,temp,attack);
            battle.push_enemy(ene);          
        }
        else{
            cout<<name<<" is out of fight"<<endl;
        }
    }
    string begin;
    cin>>begin;
    battle.startBattle();
}
