//Kūrė Dominykas Rakūnas, kreditai man :D
///Patogiau ir standartas yra vietoj char[][]
///naudoti std arba stl bibliotekas, šiuo atveju std::string ir std::vector
///Bet šiaip viskas beveik pagal taisykles
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <string.h>

int gautiLaikoSkirtuma(int start[3], int finish[3]);
int rikiuotiPagalLaika(std::pair<char*, int> a, std::pair<char*, int> b);
void rikiuotiGalutiniusRezultatus(std::vector<std::pair<char*, int> > * rezVector, int * m);
void irasytiGalutiniusRezultatus(std::vector<std::pair<char*, int> > * rezVector, int * m, std::ofstream * out);

int main(){
    setlocale(LC_ALL, "Lithuanian");
    using namespace std;
    ifstream in("U2.txt");
    ofstream out("U2rez.txt");
    int n, m;
    in>>n;
    int maxChars = 20;
    int bufferSize = maxChars+1; ///+1 nes naudoju seną būdą, kur reikia papildomos vietos užtikrint terminuotuojui '\0'
    char vardaiStart[n][bufferSize];
    char vardaiFinish[n][bufferSize];
    int laikaiStart[n][3];
    int laikaiFinish[n][3];

    //----------||--------------------------//
    ///---Irašau slidininkų pradėjimo duomenis

    for(int i=0; i<n; i++){
        in.ignore(1, '\n');
        in.read(vardaiStart[i], bufferSize);
        vardaiStart[i][maxChars] = '\0'; ///'\0' ištrina nereikalingus duomenis po "maxChars" kiekio bitų
        in>>laikaiStart[i][0];
        in>>laikaiStart[i][1];
        in>>laikaiStart[i][2];
    }

    //----------||--------------------------//
    ///---Irašau slidininkų pabaigimo duomenis
    in>>m;
    for(int i=0; i<m; i++){
        in.ignore(1, '\n');///Kadangi naudoju C ir C++, tai nuskaitęs sveikuosius (int) skaičius, turiu nuskaičiuoti ir ignoruoti
        in.read(vardaiFinish[i], bufferSize);///'\n', jo nenuskaito, nes char* nėra (int), bet jį traktuoja, kaip realų simbolį
        vardaiFinish[i][maxChars] = '\0';
        in>>laikaiFinish[i][0];
        in>>laikaiFinish[i][1];
        in>>laikaiFinish[i][2];
    }
    //-------------------------------------||-------------------------------------//
    ///---Surandu žmonių pradžios ir pabaigos laikus ir sudedu nuosekliai į vektorių
    vector<pair<char*, int> > rezVector;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(strcmp(vardaiFinish[i],vardaiStart[j])==0){///jeigu randa, kad reikšmės su i ir j indeksais vienoti - sujungia
                rezVector.push_back(pair<char*, int>(vardaiFinish[i], gautiLaikoSkirtuma(laikaiStart[j], laikaiFinish[i])));
                break;
            }
        }
    }


    rikiuotiGalutiniusRezultatus(&rezVector, &m);

    irasytiGalutiniusRezultatus(&rezVector, &m, &out);
    return 0;
}

 int gautiLaikoSkirtuma(int start[3], int finish[3]){
    int startTimeInSec;
    int finishTimeInSec;
    int skirtumas;
    startTimeInSec = (start[0]*3600)+(start[1]*60) + start[2];
    finishTimeInSec = (finish[0]*3600)+(finish[1]*60) + finish[2];
    skirtumas = finishTimeInSec-startTimeInSec;
    return skirtumas;
 }
 int rikiuotiPagalLaika(std::pair<char*, int> a, std::pair<char*, int> b){
    return a.second<b.second;
}

void rikiuotiGalutiniusRezultatus(std::vector<std::pair<char*, int> > * rezVector, int * m){
    std::sort((*rezVector).begin(), (*rezVector).end(), rikiuotiPagalLaika);
    char* tempPair; ///Pointeris reikškia masyva(sena C)
    for(int i=0; i<*m; i++){
        for(int j=i+1; j<*m-1; j++){
            if((*rezVector)[i].second == (*rezVector)[j].second){
                if(strcmp((*rezVector)[i].first, (*rezVector)[j].first)>0){
                    tempPair = (*rezVector)[i].first;
                    (*rezVector)[i].first = (*rezVector)[j].first;
                    (*rezVector)[j].first = tempPair;
                }
            }
        }
    }
}
void irasytiGalutiniusRezultatus(std::vector<std::pair<char*, int> > * rezVector, int * m, std::ofstream * out){
    for(int i=0; i<*m; i++){
        *out<<(*rezVector)[i].first<<" "<<(*rezVector)[i].second/60<<" "<<(*rezVector)[i].second%60<<std::endl;
    }
}

